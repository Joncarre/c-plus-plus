# Ordering patients in the emergency department

In the ACR Hospital (Aquı Curamos Rapido) they have started to improve the Emergency Department so that the patients who arrive with more serious ailments are attended before the others. For that, they have bought a UCM (Medical Cataloguing Unit) that is able to instantly assess the status of a patient with an integer between 0 and 1,000,000, where 0 indicates that his condition is minor (perhaps even nonexistent and is a mere hypochondriac) and 1,000,000 indicates that the patient is almost walking towards the light.

Unfortunately, the influx of patients is such that even then it is very difficult to know quickly who should be the next to be seen. New patients keep coming in while the more serious ones are being treated, and it is not easy to keep them in order. When a doctor is free, the waiting patient with a more serious assessment should be seen. If there are two patients assessed to be of equal severity, the one who has been waiting the longest should be seen.

To help in the task of deciding who is next, ACR has put out a call for help among the best programmers. Are you one of them?

**Input**

The input consists of several test cases. Each case starts with a line indicating the number n of events that will occur (at most 200,000), and then there are n lines each with one event.
each with an event. An event can be the arrival of a new patient, or the care by a physician of the most urgent patient who has been released. New patient admissions are indicated in the form I name severity, where name is a string of at most 20 characters (no spaces) and severity is a number between 0 and 1,000,000 with its status (0 mild, 1,000,000 very severe). The events in which the next patient is attended are indicated by the character A. It is guaranteed that there will never be events of type A if there are no patients waiting. The entry ends when the number of events is 0.

**Output**

For each type A event of each test case, the name of the patient being attended at that time will be written. The most serious patient is seen first and, in case of equality between two or more patients, the one who has been waiting the longest will be chosen from among them. At the end of the treatment of each case, one more line with four hyphens is written (----).

**Input example**

    9
    I Alberto 4000
    I Pepe 3000
    A
    I Rosa 2000
    I Laura 5000
    A
    I Sara 3000
    A
    A
    0

**Output example**

    Alberto
    Laura
    Pepe
    Sara
    ----

**Author:** Alberto Verdejo.
