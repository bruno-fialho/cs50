import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import re

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get cash from users
    user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    cash=user[0]["cash"]

    # Get symbol, company_name and shares from portfolio and add to a dict
    portfolio = db.execute("SELECT symbol, company_name, shares FROM portfolios WHERE user_id = ? ORDER BY symbol ASC", session["user_id"])

    # Start a variable for invested money
    invested_cash = 0

    # Add actual stock price and total value to portfolio dict
    for company in portfolio:
        stock = lookup(company["symbol"])

        company["price"]=usd(stock["price"])

        company["total"]=usd(float(stock["price"]) * int(company["shares"]))

        invested_cash += (float(stock["price"]) * int(company["shares"]))

    # Calculate total money
    total_cash = invested_cash + cash

    return render_template("index.html", cash=cash, portfolio=portfolio, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Get the stock data
        stock = lookup(request.form.get("symbol"))

        # Ensure the symbol is valid
        if not stock:
            return apology("invalid symbol", 403)

        # Ensure shares was submitted
        new_shares = int(request.form.get("shares"))

        if not new_shares:
            return apology("must provide shares", 403)

        transaction_value = new_shares * float(stock["price"])

        # Ensure user has enough cash
        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        if float(user[0]["cash"]) < transaction_value:
            return apology("can't afford", 403)

        # Insert buy into transactions
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares) VALUES (:user_id, :symbol, :price, :shares)",
            user_id=session["user_id"], symbol=stock["symbol"], price=stock["price"], shares=new_shares)

        # Insert or Update user's portfolio
        old_shares = db.execute("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?",
            session["user_id"], stock["symbol"])

        # Insert if there is no stocks from the company in users portfolio
        if not old_shares:
            db.execute("INSERT INTO portfolios (user_id, symbol, company_name, shares) VALUES (:user_id, :symbol, :company_name, :shares)",
                user_id=session["user_id"], symbol=stock["symbol"], company_name=stock["name"], shares=new_shares)

        # Update if the user has other stocks from the company already
        else:
            new_shares += old_shares[0]['shares']

            db.execute("UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?",
                new_shares, session["user_id"], stock["symbol"])

        # Update cash value
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                float(user[0]["cash"])-transaction_value , session["user_id"])

        # Redirect user to home page (AND SHOW ALERT)
        flash("Bought!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get symbol, shares, price and datetime from transactions and add to a dict
    transactions = db.execute("SELECT symbol, shares, price, datetime FROM transactions WHERE user_id = ? ORDER BY datetime DESC", session["user_id"])

    # # Add actual stock price and total value to portfolio dict
    # for transactionjs in transactions:
    #     stock = lookup(company["symbol"])

    #     company["price"]=usd(stock["price"])

    #     company["total"]=usd(float(stock["price"]) * int(company["shares"]))

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Get the stock data
        stock = lookup(request.form.get("symbol"))

        # Ensure the symbol is valid
        if not stock:
            return apology("invalid symbol", 403)

        # Redirect user to home page
        return render_template("/quoted.html", name=stock["name"], symbol=stock["symbol"], price=stock["price"])

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username does not exists
        if len(rows) == 1:
            return apology("this username is not available", 403)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password has letters, numbers and symbols
        if not password_strength_checker(request.form.get("password")):
            return apology("password must have 6-12 digits, 1 uppercase and 1 special character", 403)

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 403)

        # Ensure confirmation and password match
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("confirmation must match password", 403)

        # Inset new user into user
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username=request.form.get("username"),
            hash=generate_password_hash(request.form.get("password")))

        # Query database for id
        rows = db.execute("SELECT id FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("Registered!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Get the stock data
        stock = lookup(request.form.get("symbol"))

        # Ensure the symbol is valid
        if not stock:
            return apology("invalid symbol", 403)

        # Ensure the user has any shares of the stock
        old_shares = db.execute("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?",
            session["user_id"], stock["symbol"])

        print(old_shares)

        if not old_shares:
            return apology("you don't have these shares", 403)

        # Ensure shares was submitted
        sell_shares = int(request.form.get("shares"))

        if not sell_shares:
            return apology("must provide shares", 403)

        # Ensure user has enough shares
        if (old_shares[0]["shares"]) < sell_shares:
            return apology("too much shares", 403)

        # Calculate transaction value
        transaction_value = sell_shares * float(stock["price"])

        # Insert sell into transactions
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares) VALUES (:user_id, :symbol, :price, :shares)",
            user_id=session["user_id"], symbol=stock["symbol"], price=stock["price"], shares=sell_shares*(-1))

        # Update user's portfolio
        new_shares = old_shares[0]['shares'] - sell_shares

        db.execute("UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?",
            new_shares, session["user_id"], stock["symbol"])

        # Update cash value
        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
            float(user[0]["cash"])+transaction_value , session["user_id"])

        # Redirect user to home page (AND SHOW ALERT)
        flash("Sold!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Get symbols from portfolio and add to a dict
        portfolio = db.execute("SELECT symbol FROM portfolios WHERE user_id = ? ORDER BY symbol ASC", session["user_id"])

        return render_template("sell.html", portfolio=portfolio)

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change password"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide a new password", 403)

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 403)

        # Ensure confirmation and password match
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("confirmation must match password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])

        # Ensure password is new
        if check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("provide a new password", 403)

        # Update password into users
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("password")), session["user_id"])

        # Redirect user to home page
        flash("Changed!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("password.html")

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Deposit more cash"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure flag was submitted
        if not request.form.get("flag"):
            return apology("must provide a credit card flag", 403)

        # Get the deposit value
        deposit = int(request.form.get("cash"))

        # Ensure cash was submitted
        if not deposit:
            return apology("must provide cash", 403)

        # Update cash value
        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
            float(user[0]["cash"])+deposit , session["user_id"])

        # Redirect user to home page (AND SHOW ALERT)
        flash("Deposited!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Get symbols from portfolio and add to a dict
        flags = ['AMEX', 'MASTERCARD', 'VISA']

        return render_template("deposit.html", flags=flags)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

# Adapted from https://github.com/AshkarSidheeque/password-strength-checker
def password_strength_checker(p):
    x = True
    while x:
        if (len(p)<6 or len(p)>12):
            break
        elif not re.search("[A-Z]",p):
            break
        elif not re.search("[$#@]",p):
            break
        elif re.search("\s",p):
            break

        else:
            return True

    if x:
        return False