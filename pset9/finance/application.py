import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime
import re

# Configure application.
app = Flask(__name__)

# Ensure templates are auto-reloaded.
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
    records = db.execute(
        "SELECT user_id, symbol, name, SUM(shares), price, time FROM purchase WHERE user_id=? GROUP BY symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = 0
    for record in records:
        total += record["price"] * record["SUM(shares)"]
    grand_total = cash + total
    return render_template("index.html", records=records, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        elif quote is None:
            return apology("Invalid stock symbol!", 400)
        elif not request.form.get("shares") or request.form.get("shares").isalpha() == True:
            return apology("shares cannot be empty or non-numeric", 400)
        else:
            # Check the case that user has.
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
            price = quote["price"]
            try:
                shares = int(request.form.get("shares"))
                if shares < 1:
                    return apology("shares must be a positive integer", 400)
            except ValueError:
                return apology("shares must be a positive integer", 400)

            # Remaining price that user has after buying the shares.
            balance = user_cash - price * shares

            # Check if user have the insufficient balance.
            if balance < 0:
                return apology("Sorry, you cannot purchase due to insufficient cash!", 400)
            else:
                db.execute("Update users SET cash=? WHERE id=?", balance, session["user_id"])
                db.execute("INSERT INTO purchase (user_id, symbol, name, shares, price, time) VALUES (?, ?, ?, ?, ?, ?)",
                           session["user_id"], request.form.get("symbol"), quote["name"], shares, price, datetime.datetime.now())
            flash("Bought!")
            return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM purchase WHERE user_id=? ORDER BY time", session["user_id"])
    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote is None:
            return apology("Please provide a valid stock symbol.")
        else:
            return render_template("quoted.html", name=quote["name"], price=quote["price"], symbol=quote["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # if username exists render apology
        elif len(rows) == 1:
            return apology("user name already exists", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure that passward and confirmation password matches.
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password do not match", 400)

        else:
            # Convert the password into hash password.
            Hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
            # Enter the new user into the table
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), Hash)
            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        current_shares = db.execute("SELECT SUM(shares) FROM purchase WHERE user_id = ? AND symbol = ?",
                                    session["user_id"], quote["symbol"])[0]
        # User must enter positive and valid number of shares.
        try:
            shares = int(request.form.get("shares"))
            if shares < 1:
                return apology("shares must be a positive integer", 400)
        except ValueError:
            return apology("share must be a positive integer", 400)
        # Must provide a valid stock symbol.
        if not request.form.get("symbol"):
            return apology("must provide the stock symbol that you want to sell", 400)
        elif quote is None:
            return apology("Invalid stock symbol!", 400)
        elif int(request.form.get("shares")) > current_shares["SUM(shares)"]:
            return apology("not have enough shares", 400)
        else:
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
            price = quote["price"]
            new_balance = user_cash + price * int(request.form.get("shares"))
            # update new balance.
            db.execute("UPDATE users SET cash=? WHERE id=?", new_balance, session["user_id"])
            # Record of the table.
            db.execute("INSERT INTO purchase (user_id, symbol, name, shares, price, time) VALUES(?, ?, ?, ?, ?, ?)",
                       session["user_id"], quote["symbol"], quote["name"], -int(request.form.get("shares")), price, datetime.datetime.now())
        flash("Sold!")
        return redirect("/")
    available_stocks = db.execute("SELECT DISTINCT symbol FROM purchase WHERE user_id=?", session["user_id"])
    return render_template("sell.html", available_stocks=available_stocks)




def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)




