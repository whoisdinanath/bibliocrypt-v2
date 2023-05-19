import csv
import random_isbn
import random_name
import random_book

with open('books.csv', 'w') as file:
    # create a csv writer object
    writer = csv.writer(file)
    # write header
    writer.writerow(['TITLE', 'AUTHOR', 'ISBN', 'OWNER_ID'])
    n = int(input("Enter the number of books to be generated: "))
    # generate n random books and write to csv file
    for _ in range(n):
        OWNER_ID = "00000000"
        book = random_book.generate_book_title()
        author = random_name.generate_name()
        author = author[0] + " " + author[1]
        isbn = random_isbn.generate_ISBN()
        writer.writerow([book, author, isbn, OWNER_ID])
