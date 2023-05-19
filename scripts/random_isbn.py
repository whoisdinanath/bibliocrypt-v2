import random

def generate_ISBN():
    # Generate the first 12 digits
    digits = [random.randint(0, 9) for _ in range(12)]
    # Compute the check digit
    sum = 0
    for i in range(12):
        digit = digits[i]
        sum += digit if i % 2 == 0 else 3 * digit
    check_digit = (10 - (sum % 10)) % 10
    # Append the check digit and return the ISBN as a string
    digits.append(check_digit)
    isbn = ''.join(str(d) for d in digits)
    return isbn

def is_ISBN_valid(isbn):
    # Strip non-numeric characters
    stripped = ''.join(c for c in isbn if c.isdigit())
    if len(stripped) != 13:
        return False
    # Compute the check digit
    sum = 0
    for i in range(12):
        digit = int(stripped[i])
        sum += digit if i % 2 == 0 else 3 * digit
    check_digit = (10 - (sum % 10)) % 10
    actual_check_digit = int(stripped[12])
    return check_digit == actual_check_digit

# Generate a random ISBN and check if it is valid
while True:
    isbn = generate_ISBN()
    if is_ISBN_valid(isbn):
        break

print(isbn)
