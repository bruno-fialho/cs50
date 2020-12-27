import os

from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.utils import secure_filename

from helpers import checksum, grayscale, sepia, reflect
import urllib.request
import re

# Configure upload folder
UPLOAD_FOLDER = 'static/uploads/'

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

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_TYPE"] = "filesystem"
app.secret_key = "secret key"
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024
Session(app)

# Check if upload image is valid
ALLOWED_EXTENSIONS = set(['bmp'])

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


@app.route("/")
def index():
    """Show index page"""

    return render_template("index.html")


@app.route("/credit", methods=["GET", "POST"])
def credit():
    """Validate credit card numbers"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure credit card number was submitted
        if not request.form.get("number"):
            flash("must provide number")

        # Set a variable to input number
        number = int(request.form.get("number"))

        # Get the length of number
        length = len(str(number))

        # Get first and second digit
        first_digit = int(str(number)[0])
        second_digit = int(str(number)[1])

        # For length = 13 - Check if it is VISA
        if length == 13 and first_digit == 4 and checksum(number):
            result = "VISA"
            flash(result + "!")

        # For length = 15 - Check if it is AMEX
        elif length == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7) and checksum(number):
            result = "AMEX"
            flash(result + "!")

        # For length = 16 - Check if it is VISA
        elif length == 16 and first_digit == 4 and checksum(number):
            result = "VISA"
            flash(result + "!")

        # For length = 16 - Check if it is MASTERCARD
        elif length == 16 and first_digit == 5 and second_digit > 0 and second_digit < 6 and checksum(number):
            result = "MASTERCARD"
            flash(result + "!")

        # If number is not valid
        else:
            result = "INVALID"
            flash(result + "!")

        # Redirect user to home page (AND SHOW ALERT)
        return render_template("credit.html", number=number, result=result)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("credit.html")

@app.route("/readability", methods=["GET", "POST"])
def readability():
    """Compute a text grade level"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure credit card number was submitted
        if not request.form.get("text"):
            flash("must provide text")

        # Set a variable to input text
        text = request.form.get("text")

        # Declare variables
        letters = 0
        words = 1
        sentences = 0
        index = 0

        length = len(text)

        # Loop through the text
        for i in range(length):

            # Get the character at position 'i'
            character = text[i]

            # Check if is alpha and add to letters
            if character.isalpha():
                letters += 1

            # Check if is space and add to words
            elif character == ' ':
                words += 1

            # Check if is '.', '!' or '?' and add to sentences
            elif character == '.' or character == '!' or character == '?':
                sentences += 1

        # L = average number of letters per 100 words in the text
        L = float((letters * 100) / words)

        # S = average number of sentences per 100 words in the text
        S = float((sentences * 100) / words)

        # Calculate Coleman-Liau Index
        index = round(0.0588 * L - 0.296 * S - 15.8)

        # Print the grade level of the text
        if index > 16:
            result = "Grade 16+"
            flash(result)

        elif (index < 1):
            result = "Before Grade 1"
            flash(result)

        else:
            result = "Grade " + str(index)
            flash(result)

        # Redirect user to home page (AND SHOW ALERT)
        return render_template("readability.html", text=text, result=result)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("readability.html")

@app.route("/filters", methods=["GET", "POST"])
def filter():
    """Apply an instagram like filter"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)

        file = request.files['file']

        if file.filename == '':
            flash('No image selected for uploading')
            return redirect(request.url)

        # Ensure credit card number was submitted
        if not request.form["customRadio"]:
            flash('No filter selected')
            return redirect(request.url)
        
        # Get chosen filter
        filter = request.form["customRadio"]

        # Check if file format is allowed
        if not allowed_file(file.filename):
            flash('Allowed image types are: .bmp')
            return redirect(request.url)
        
        # Apply filter
        if filter == 'grayscale':
            filename = 'grayscale.bmp'
            filtername = 'Grayscale'
            filtered_image = grayscale(file)
        
        elif filter == 'reflect':
            filename = 'reflect.bmp'
            filtername = 'Reflect'
            filtered_image = reflect(file)   

        elif filter == 'sepia':
            filename = 'sepia.bmp'
            filtername = 'Sepia'
            filtered_image = sepia(file)

        filtered_image.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))

        flash('Image successfully uploaded and displayed')
        return render_template("filtered.html", filename=filename, filtername=filtername)
        
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("filters.html")

@app.route('/display/<filename>')
def display_image(filename):
	#print('display_image filename: ' + filename)
	return redirect(url_for('static', filename='uploads/' + filename), code=301)
