import random

# List of male and female names to choose from
male_names = ["Adam", "Alex", "Brian", "Charles", "David", "Edward", "Frank", "George", "Henry", "Ian", "John", "Kevin", "Larry",
              "Michael", "Nathan", "Oscar", "Peter", "Quincy", "Robert", "Samuel", "Thomas", "Victor", "William", "Xander", "Yankee", "Zachary"]
female_names = ["Abby", "Beth", "Cathy", "Diana", "Elizabeth", "Fiona", "Grace", "Hannah", "Isabella", "Julia", "Kate", "Linda",
                "Mary", "Nancy", "Olivia", "Penelope", "Queenie", "Rachel", "Sarah", "Tina", "Ursula", "Victoria", "Wendy", "Xia", "Yolanda", "Zoe"]

# List of surnames to choose from
surnames = ["Anderson", "Brown", "Clark", "Davis", "Evans", "Foster", "Garcia", "Harris", "Jackson", "Kim", "Lee", "Martin",
            "Nelson", "Olsen", "Parker", "Quinn", "Roberts", "Smith", "Taylor", "Upton", "Vargas", "Walker", "Xu", "Young", "Zhang"]

# Function to generate a random name and surname


def generate_name():
    gender = random.choice(["M", "F"])  # Choose male or female
    if gender == "M":
        name = random.choice(male_names)
    else:
        name = random.choice(female_names)
    surname = random.choice(surnames)
    return name, surname
