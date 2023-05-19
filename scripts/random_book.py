import random

# List of adjectives to choose from
adjectives = ["Adventurous", "Brave", "Curious", "Daring", "Eager", "Famous", "Glorious", "Happy", "Important", "Jolly", "Kind", "Lucky", "Mighty",
              "Noble", "Outstanding", "Proud", "Quick", "Radiant", "Smart", "Trusty", "Unforgettable", "Valiant", "Witty", "X-traordinary", "Youthful", "Zesty"]

# List of nouns to choose from
nouns = ["Adventurer", "Bookworm", "Champion", "Detective", "Explorer", "Friend", "Guru", "Hero", "Inventor", "Jester", "Knight", "Legend", "Mastermind",
         "Navigator", "Opportunist", "Pirate", "Quester", "Ranger", "Scholar", "Traveler", "Unicorn", "Viking", "Wizard", "Xplorer", "Youth", "Zookeeper"]

# List of suffixes to choose from
suffixes = ["Chronicles", "Diaries", "Encounters", "Fables", "Gazette", "Happenings", "Innovations", "Journeys", "Kaleidoscope", "Legacies",
            "Memoirs", "Novels", "Odyssey", "Passages", "Quests", "Revelations", "Stories", "Tales", "Universe", "Voyage", "Wonders", "X-Files", "Years", "Zeal"]

# Function to generate a random book title


def generate_book_title():
    adjective = random.choice(adjectives)
    noun = random.choice(nouns)
    suffix = random.choice(suffixes)
    title = adjective + " " + noun + " " + suffix
    return title
