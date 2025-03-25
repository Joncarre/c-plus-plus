# Horror movie marathon

The film library has organized a marathon of horror movies. During 24 hours films (all different) will be screened in the various rooms available.

Deborah Cinema, a great fan of this genre of movies, has obtained the complete program where all the movies that will be screened during the marathon are listed; along with the title, name of the director, screening room and other information of interest, the start time and duration of the movie is indicated.

Can you help Deborah plan her movie marathon, keeping in mind that her only goal is to see as many films as possible?

**Input**

The input consists of a series of test cases. Each one starts with a line with the number N of movies to be screened (0 < N <= 1,000). Next, N lines will appear with the information for each movie: the start time within the screening day, in the format HH:MM, and the duration in minutes of the movie. No film will end after 12:00 midnight. The entry will end with a case with no films, which should not be processed.

**Output**

For each test case a line will be written with the maximum number of movies Deborah Cinema can watch, assuming that she always needs 10 minutes free (to buy popcorn, change the theater, etc.) between movies.

**Inout example**

    4
    09:30 90
    12:00 80
    16:00 120
    17:30 100
    3
    10:30 90
    16:00 110
    12:00 70
    2
    10:30 90
    12:10 70

**Output example**

    3
    2
    2

**Author:** Alberto Verdejo.
