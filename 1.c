#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define CLEAR_SCREEN system("cls")
#else
#include <unistd.h>
#define CLEAR_SCREEN system("clear")
#define getch() getchar() 
#endif

// ---------- STRUCTURES ----------
struct Patient {
    int id;
    char name[50];
    int age;
    char gender[15];
    char disease[50];
    char date[15];
    int doctorId;
};

struct Doctor {
    int id;
    char name[50];
    char specialty[50];
    char shift[20];
};

// ---------- PROTOTYPES ----------
void login();
void adminMenu();
void staffMenu();
void patientMenu();
void doctorMenu();
void billingMenu();

void addPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void deletePatient();
void countPatients();
int isPatientIdUnique(int);

void addDoctor();
void viewDoctors();
void searchDoctor();
int isDoctorIdUnique(int);

void generateBill();

// ---------- COLOR ----------
void color(int c) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
#endif
}

// ---------- PAUSE ----------
void pauseScreen() {
    printf("\nPress ENTER to continue...");
    fflush(stdin);
    getchar();
    getchar();
}

// ---------- PASSWORD ----------
void getPassword(char *pass) {
    int i = 0;
    char ch;
    while ((ch = getch()) != 13 && ch != 10) { 
        if (ch == 8 && i > 0) { // Backspace
            i--;
            printf("\b \b");
        } else {
            pass[i++] = ch;
            printf("*");
        }
    }
    pass[i] = '\0';
}

// ---------- HEADER ----------
void header() {
    CLEAR_SCREEN;
    
    color(11); // Cyan
    printf(" _   _  _____  _____  ______ _____ _____  ___   _     \n");
    printf("| | | ||  _  |/  ___| | ___ \\_   _|_   _|/ _ \\ | |    \n");
    printf("| |_| || | | |\\ `--.  | |_/ / | |   | | / /_\\ \\| |    \n");
    printf("|  _  || | | | `--. \\ |  __/  | |   | | |  _  || |    \n");
    printf("| | | |\\ \\_/ //\\__/ / | |    _| |_  | | | | | || |____\n");
    printf("\\_| |_/ \\___/ \\____/  \\_|    \\___/  \\_/ \\_| |_/\\_____/\n\n");

    color(10); // Green
    printf(" ___  ___  ___   _   _   ___  _____  _____ ___  ___ _____ _   _ _____ \n");
    printf("|  \\/  | / _ \\ | \\ | | / _ \\|  __ \\|  ___||  \\/  ||  ___|| \\ | |_   _|\n");
    printf("| .  . |/ /_\\ \\|  \\| |/ /_\\ \\ |  \\/| |__  | .  . || |__  |  \\| | | |  \n");
    printf("| |\\/| ||  _  || . ` ||  _  | | __ |  __| | |\\/| ||  __| | . ` | | |  \n");
    printf("| |  | || | | || |\\  || | | | |_\\ \\| |___ | |  | || |___ | |\\  | | |  \n");
    printf("\\_|  |_/\\_| |_/\\_| \\_/\\_| |_/\\____/\\____/ \\_|  |_/\\____/ \\_| \\_/ \\_/  \n\n");

    color(14); // Yellow
    printf(" _____ __   __ _____ _____ _____ ___  ___\n");
    printf("/  ___|\\ \\ / //  ___|_   _|  ___||  \\/  |\n");
    printf("\\ `--.  \\ V / \\ `--.  | | | |__  | .  . |\n");
    printf(" `--. \\  \\ /   `--. \\ | | |  __| | |\\/| |\n");
    printf("/\\__/ /  | |  /\\__/ / | | | |___ | |  | |\n");
    printf("\\____/   \\_/  \\____/  \\_/ \\____/ \\_|  |_/\n\n");

    color(15); 
}

// ---------- MAIN ----------
int main() {
    login();
    return 0;
}

// ---------- LOGIN ----------
void login() {
    char user[20], pass[20];
    int attempts = 0;

    while (attempts < 3) {
        header();
        color(11); printf("LOGIN PAGE\n"); color(7);

        printf("Username: ");
        scanf("%s", user);
        printf("Password: ");
        getPassword(pass);

        if (!strcmp(user, "admin") && !strcmp(pass, "admin123")) {
            color(10); printf("\n\nAdmin Login Successful!\n"); color(7);
            pauseScreen();
            adminMenu();
            return;
        }
        else if (!strcmp(user, "staff") && !strcmp(pass, "staff123")) {
            color(10); printf("\n\nStaff Login Successful!\n"); color(7);
            pauseScreen();
            staffMenu();
            return;
        } else {
            attempts++;
            color(12); printf("\n\nInvalid credentials! [%d/3 attempts]\n", attempts); color(7);
            pauseScreen();
        }
    }
    exit(0);
}

// ---------- MENUS ----------
void adminMenu() {
    int ch;
    while (1) {
        header();
        color(14);
        printf("--- ADMIN PANEL ---\n");
        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Billing System\n");
        printf("4. Logout\n");
        color(7);
        printf("\nChoice: ");
        scanf("%d", &ch);

        if (ch == 1) patientMenu();
        else if (ch == 2) doctorMenu();
        else if (ch == 3) billingMenu();
        else if (ch == 4) return;
    }
}

void staffMenu() {
    int ch;
    while (1) {
        header();
        color(14);
        printf("--- STAFF PANEL ---\n");
        printf("1. View Patients\n");
        printf("2. Search Patient\n");
        printf("3. View Doctors\n");
        printf("4. Logout\n");
        color(7);
        printf("\nChoice: ");
        scanf("%d", &ch);

        if (ch == 1) viewPatients();
        else if (ch == 2) searchPatient();
        else if (ch == 3) viewDoctors();
        else if (ch == 4) return;
        pauseScreen();
    }
}

void patientMenu() {
    int ch;
    while (1) {
        header();
        color(14);
        printf("--- PATIENT MANAGEMENT ---\n");
        printf("1. Add Patient\n2. View Patients\n3. Search Patient\n4. Update Patient\n5. Delete Patient\n6. Count Patients\n7. Back\n");
        color(7);
        printf("Choice: ");
        scanf("%d", &ch);

        if (ch == 1) addPatient();
        else if (ch == 2) viewPatients();
        else if (ch == 3) searchPatient();
        else if (ch == 4) updatePatient();
        else if (ch == 5) deletePatient();
        else if (ch == 6) countPatients();
        else if (ch == 7) return;
        pauseScreen();
    }
}

void doctorMenu() {
    int ch;
    while (1) {
        header();
        color(14);
        printf("--- DOCTOR MANAGEMENT ---\n");
        printf("1. Add Doctor\n2. View Doctors\n3. Search Doctor\n4. Back\n");
        color(7);
        printf("Choice: ");
        scanf("%d", &ch);

        if (ch == 1) addDoctor();
        else if (ch == 2) viewDoctors();
        else if (ch == 3) searchDoctor();
        else if (ch == 4) return;
        pauseScreen();
    }
}

void billingMenu() {
    header();
    color(14);
    printf("--- BILLING SYSTEM ---\n");
    color(7);
    generateBill();
    pauseScreen();
}

// ---------- PATIENT FUNCTIONS ----------
void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    struct Patient p;
    printf("Patient ID: "); scanf("%d", &p.id);
    if (!isPatientIdUnique(p.id)) {
        color(12); printf("ID exists!\n"); color(7);
        fclose(fp); return;
    }
    printf("Name: "); scanf(" %[^\n]", p.name);
    printf("Age: "); scanf("%d", &p.age);
    printf("Gender: "); scanf(" %[^\n]", p.gender);
    printf("Disease: "); scanf(" %[^\n]", p.disease);
    printf("Date: "); scanf(" %[^\n]", p.date);
    printf("Doctor ID: "); scanf("%d", &p.doctorId);
    fwrite(&p, sizeof p, 1, fp);
    fclose(fp);
    color(10); printf("Patient added!\n"); color(7);
}

void viewPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;
    if (!fp) { printf("No records.\n"); return; }
    color(11);
    printf("\n%-4s %-15s %-4s %-10s %-15s %-12s %-8s\n","ID","Name","Age","Gender","Disease","Date","DrID");
    color(7);
    while (fread(&p, sizeof p, 1, fp))
        printf("%-4d %-15s %-4d %-10s %-15s %-12s %-8d\n",p.id,p.name,p.age,p.gender,p.disease,p.date,p.doctorId);
    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;
    int id, found = 0;
    printf("Enter Patient ID: "); scanf("%d", &id);
    while (fread(&p, sizeof p, 1, fp)) {
        if (p.id == id) {
            found = 1;
            printf("\nName: %s\nDisease: %s\n", p.name, p.disease);
            break;
        }
    }
    if (!found) printf("Not found.\n");
    fclose(fp);
}

void updatePatient() {
    FILE *fp = fopen("patients.dat", "rb");
    FILE *ft = fopen("temp.dat", "wb");
    struct Patient p;
    int id, found = 0;
    printf("ID to update: "); scanf("%d", &id);
    while (fread(&p, sizeof p, 1, fp)) {
        if (p.id == id) {
            found = 1;
            printf("New Disease: "); scanf(" %[^\n]", p.disease);
        }
        fwrite(&p, sizeof p, 1, ft);
    }
    fclose(fp); fclose(ft);
    remove("patients.dat"); rename("temp.dat", "patients.dat");
    printf(found ? "Updated!\n" : "Not found!\n");
}

void deletePatient() {
    FILE *fp = fopen("patients.dat", "rb");
    FILE *ft = fopen("temp.dat", "wb");
    struct Patient p;
    int id, found = 0;
    printf("ID to delete: "); scanf("%d", &id);
    while (fread(&p, sizeof p, 1, fp)) {
        if (p.id == id) found = 1;
        else fwrite(&p, sizeof p, 1, ft);
    }
    fclose(fp); fclose(ft);
    remove("patients.dat"); rename("temp.dat", "patients.dat");
    printf(found ? "Deleted!\n" : "Not found!\n");
}

void countPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    if(!fp) { printf("Total: 0\n"); return; }
    fseek(fp, 0, SEEK_END);
    printf("Total Patients: %ld\n", ftell(fp)/sizeof(struct Patient));
    fclose(fp);
}

// ---------- DOCTOR FUNCTIONS ----------
void addDoctor() {
    FILE *fp = fopen("doctors.dat", "ab");
    struct Doctor d;
    printf("Doctor ID: "); scanf("%d", &d.id);
    if (!isDoctorIdUnique(d.id)) { printf("ID exists!\n"); fclose(fp); return; }
    printf("Name: "); scanf(" %[^\n]", d.name);
    printf("Specialty: "); scanf(" %[^\n]", d.specialty);
    printf("Shift: "); scanf(" %[^\n]", d.shift);
    fwrite(&d, sizeof d, 1, fp);
    fclose(fp);
    color(10); printf("Doctor added!\n"); color(7);
}

void viewDoctors() {
    FILE *fp = fopen("doctors.dat", "rb");
    struct Doctor d;
    if(!fp) return;
    color(11); printf("\n%-4s %-15s %-15s %-10s\n","ID","Name","Specialty","Shift"); color(7);
    while (fread(&d, sizeof d, 1, fp))
        printf("%-4d %-15s %-15s %-10s\n",d.id, d.name, d.specialty, d.shift);
    fclose(fp);
}

void searchDoctor() {
    FILE *fp = fopen("doctors.dat", "rb");
    struct Doctor d;
    int id;
    printf("Enter Doctor ID: "); scanf("%d", &id);
    while (fread(&d, sizeof d, 1, fp)) {
        if (d.id == id) {
            printf("\nDoctor: %s\nSpecialty: %s\n", d.name, d.specialty);
            fclose(fp); return;
        }
    }
    printf("Not found.\n"); fclose(fp);
}

// ---------- BILLING ----------
void generateBill() {
    int id, found = 0;
    float med, room, doc;
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;

    printf("Enter Patient ID for Billing: ");
    scanf("%d", &id);

    while (fread(&p, sizeof p, 1, fp)) {
        if (p.id == id) {
            found = 1;
            printf("\nPatient Found: %s\n", p.name);
            printf("Enter Medicine Charges: "); scanf("%f", &med);
            printf("Enter Room Charges: "); scanf("%f", &room);
            printf("Enter Doctor Consultant Fees: "); scanf("%f", &doc);

            printf("\n---------- INVOICE ----------\n");
            printf("Patient: %s\n", p.name);
            printf("Medicine: $%.2f\n", med);
            printf("Room:     $%.2f\n", room);
            printf("Doctor:   $%.2f\n", doc);
            printf("-----------------------------\n");
            printf("TOTAL:    $%.2f\n", med + room + doc);
            break;
        }
    }
    if (!found) printf("Patient ID not found.\n");
    fclose(fp);
}

// ---------- UTILS ----------
int isPatientIdUnique(int id) {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;
    if (!fp) return 1;
    while (fread(&p, sizeof p, 1, fp)) if (p.id == id) { fclose(fp); return 0; }
    fclose(fp); return 1;
}

int isDoctorIdUnique(int id) {
    FILE *fp = fopen("doctors.dat", "rb");
    struct Doctor d;
    if (!fp) return 1;
    while (fread(&d, sizeof d, 1, fp)) if (d.id == id) { fclose(fp); return 0; }
    fclose(fp); return 1;
}