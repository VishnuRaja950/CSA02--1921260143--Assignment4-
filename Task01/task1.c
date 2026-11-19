#include <stdio.h>
#include <string.h>
#define MAX_PATIENTS 100
typedef struct { int systolic, diastolic; } BloodPressure;
typedef struct { int day, month, year; } Date;
typedef struct { char name[50]; int age; char phone[11]; BloodPressure bp; Date visit_date; } Patient;
typedef struct { Patient records[MAX_PATIENTS]; int count; } PatientRegister;
int addPatient(PatientRegister *reg, const Patient *p) {
    if (reg == NULL || p == NULL || reg->count < 0 || reg->count >= MAX_PATIENTS) return 0;
    reg->records[reg->count] = *p;
    reg->count++;
    return 1;
}
int main(void) {
    PatientRegister reg = { .count = 0 };
    Patient p = {"Anu", 20, "9876543210", {120, 80}, {19, 11, 2026}};
    if (addPatient(&reg, &p)) printf("Patient added: %s, age %d\n", reg.records[0].name, reg.records[0].age);
    else puts("Register is full or invalid.");
    return 0;
}
