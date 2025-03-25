# Medical office

It is desired to implement a TAD (Abstract Data Type) that simulates the behavior of a simplified method office. The specification will make use of the types *Medium* and *Patient* which are represented by a string, and *Date* which is a class with three data: day, hour and minute. The operations of the office are the following:

- newDoctor(m): discharges a new doctor. If the new doctor already existed, it is not reported.
- requestConsult(p, m, f): a patient (p) requests a consultation with a physician (m) for a date (f). It will be verified that the patient and the physician exist and that the physician has the date available to see the patient.
- nextPatient(m): the physician (m) consults the patient whose turn it is at that moment, who will be the one with the lowest faithhca.
- attendPatient(m): eliminates the next patient of a physician (m).
- listPatients(m, f): returns a list of patients of a certain doctor (m) who have an appointment on (f).

**Input example**

    12
    nuevoMedico Hernandez
    nuevoMedico Alvarez
    pideConsulta Ana Alvarez 16 12 30
    pideConsulta Antonio Alvarez 16 12 10
    pideConsulta Alvaro Alvarez 17 10 00
    pideConsulta Alba Alvarez 17 10 15
    pideConsulta Anacleto Alvarez 17 10 55
    listaPacientes Alvarez 16
    siguientePaciente Alvarez
    atiendeConsulta Alvarez
    listaPacientes Alvarez 16
    listaPacientes Alvarez 17
    6
    nuevoMedico Hernandez
    pideConsulta Alvarez Ana 16 12 30
    pideConsulta Helena Hernandez 17 10 00
    atiendeConsulta Hernandez
    listaPacientes Hernandez 17
    atiendeConsulta Hernandez

**Output example**

    Doctor Alvarez dia 16
    Antonio 12:10
    Ana 12:30
    ---
    Siguiente Paciente doctor Alvarez
    Antonio
    ---
    Doctor Alvarez dia 16
    Ana 12:30
    ---
    Doctor Alvarez dia 17
    Alvaro 10:00
    Alba 10:15
    Anacleto 10:55
    ---
    ------
    Medico no existente
    ---
    Doctor Hernandez dia 17

    ---
    No hay pacientes
    ---
    ------
