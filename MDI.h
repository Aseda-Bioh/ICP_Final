#pragma once
#include "studentEnrollment.h"
#include "FacultyProfileForm.h"
#include "CourseManagementForm.h"
#include "StudentGradesForm.h"
#include "StudentScheduleForm.h"
#include "GradeEntryForm.h"
#include "ViewRosterForm.h"
#include "TranscriptForm.h"
#include "ManageProgramsForm.h"
#include "UserManagementForm.h"
#include "ReportGenerationForm.h"
#include "StudentProfileForm.h"
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainMDIForm : public System::Windows::Forms::Form
    {
    public:
        MainMDIForm(String^ userID, String^ userRole)
        {
            InitializeComponent();
            this->userID = userID;
            this->userRole = userRole;
            ConfigureMenuAccess();
        }

    protected:
        ~MainMDIForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::MenuStrip^ menuStrip;
        System::Windows::Forms::ToolStrip^ toolStrip;
        System::ComponentModel::Container^ components;
        String^ userID;
        String^ userRole;

        // Menu Items
        System::Windows::Forms::ToolStripMenuItem^ fileMenu;
        System::Windows::Forms::ToolStripMenuItem^ studentMenu;
        System::Windows::Forms::ToolStripMenuItem^ facultyMenu;
        System::Windows::Forms::ToolStripMenuItem^ adminMenu;
        System::Windows::Forms::ToolStripMenuItem^ helpMenu;

        // Student Menu Items
        System::Windows::Forms::ToolStripMenuItem^ studentProfileMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ enrollmentMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ viewGradesMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ viewScheduleMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ viewTranscriptMenuItem;

        // Faculty Menu Items
        System::Windows::Forms::ToolStripMenuItem^ facultyProfileMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ manageCoursesMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ enterGradesMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ viewRosterMenuItem;

        // Admin Menu Items
        System::Windows::Forms::ToolStripMenuItem^ manageProgramsMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ manageUsersMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ generateReportsMenuItem;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Form Settings
            this->IsMdiContainer = true;
            this->Text = L"University Management System";

            // Initialize MenuStrip
            this->menuStrip = gcnew MenuStrip();
            this->menuStrip->Dock = DockStyle::Top;

            // File Menu
            this->fileMenu = gcnew ToolStripMenuItem(L"File");
            ToolStripMenuItem^ logoutMenuItem = gcnew ToolStripMenuItem(L"Logout", nullptr,
                gcnew EventHandler(this, &MainMDIForm::LogoutMenuItem_Click));
            ToolStripMenuItem^ exitMenuItem = gcnew ToolStripMenuItem(L"Exit", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ExitMenuItem_Click));
            this->fileMenu->DropDownItems->AddRange(gcnew array<ToolStripItem^> {
                logoutMenuItem,
                    gcnew ToolStripSeparator(),
                    exitMenuItem
            });

            // Student Menu
            this->studentMenu = gcnew ToolStripMenuItem(L"Student");
            this->studentProfileMenuItem = gcnew ToolStripMenuItem(L"Student Profile", nullptr,
                gcnew EventHandler(this, &MainMDIForm::StudentProfileMenuItem_Click));
            this->enrollmentMenuItem = gcnew ToolStripMenuItem(L"Course Enrollment", nullptr,
                gcnew EventHandler(this, &MainMDIForm::EnrollmentMenuItem_Click));
            this->viewGradesMenuItem = gcnew ToolStripMenuItem(L"View Grades", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ViewGradesMenuItem_Click));
            this->viewScheduleMenuItem = gcnew ToolStripMenuItem(L"View Schedule", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ViewScheduleMenuItem_Click));
            this->viewTranscriptMenuItem = gcnew ToolStripMenuItem(L"View Transcript", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ViewTranscriptMenuItem_Click));
            this->studentMenu->DropDownItems->AddRange(gcnew array<ToolStripItem^> {
                this->studentProfileMenuItem,
                    this->enrollmentMenuItem,
                    this->viewGradesMenuItem,
                    this->viewScheduleMenuItem,
                    this->viewTranscriptMenuItem
            });

            // Faculty Menu
            this->facultyMenu = gcnew ToolStripMenuItem(L"Faculty");
            this->facultyProfileMenuItem = gcnew ToolStripMenuItem(L"Faculty Profile", nullptr,
                gcnew EventHandler(this, &MainMDIForm::FacultyProfileMenuItem_Click));
            this->manageCoursesMenuItem = gcnew ToolStripMenuItem(L"Manage Courses", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ManageCoursesMenuItem_Click));
            this->enterGradesMenuItem = gcnew ToolStripMenuItem(L"Enter Grades", nullptr,
                gcnew EventHandler(this, &MainMDIForm::EnterGradesMenuItem_Click));
            this->viewRosterMenuItem = gcnew ToolStripMenuItem(L"View Class Roster", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ViewRosterMenuItem_Click));
            this->facultyMenu->DropDownItems->AddRange(gcnew array<ToolStripItem^> {
                this->facultyProfileMenuItem,
                    this->manageCoursesMenuItem,
                    this->enterGradesMenuItem,
                    this->viewRosterMenuItem
            });

            // Admin Menu
            this->adminMenu = gcnew ToolStripMenuItem(L"Administration");
            this->manageProgramsMenuItem = gcnew ToolStripMenuItem(L"Manage Programs", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ManageProgramsMenuItem_Click));
            this->manageUsersMenuItem = gcnew ToolStripMenuItem(L"Manage Users", nullptr,
                gcnew EventHandler(this, &MainMDIForm::ManageUsersMenuItem_Click));
            this->generateReportsMenuItem = gcnew ToolStripMenuItem(L"Generate Reports", nullptr,
                gcnew EventHandler(this, &MainMDIForm::GenerateReportsMenuItem_Click));
            this->adminMenu->DropDownItems->AddRange(gcnew array<ToolStripItem^> {
                this->manageProgramsMenuItem,
                    this->manageUsersMenuItem,
                    this->generateReportsMenuItem
            });

            // Help Menu
            this->helpMenu = gcnew ToolStripMenuItem(L"Help");
            ToolStripMenuItem^ aboutMenuItem = gcnew ToolStripMenuItem(L"About", nullptr,
                gcnew EventHandler(this, &MainMDIForm::AboutMenuItem_Click));
            this->helpMenu->DropDownItems->Add(aboutMenuItem);

            // Add Menus to MenuStrip
            this->menuStrip->Items->AddRange(gcnew array<ToolStripItem^> {
                this->fileMenu,
                    this->studentMenu,
                    this->facultyMenu,
                    this->adminMenu,
                    this->helpMenu
            });

            // Add MenuStrip and ToolStrip to Form
            this->Controls->Add(this->menuStrip);
            this->Controls->Add(this->toolStrip);
            this->MainMenuStrip = this->menuStrip;
        }

        void ConfigureMenuAccess()
        {
            // Hide menus based on user role
            if (this->userRole == "STUDENT") {
                this->facultyMenu->Visible = false;
                this->adminMenu->Visible = false;
            }
            else if (this->userRole == "FACULTY") {
                this->studentMenu->Visible = false;
                this->adminMenu->Visible = false;
            }
            else if (this->userRole == "ADMIN") {
                this->studentMenu->Visible = false;
                this->facultyMenu->Visible = false;
            }
        }

        // Menu Item Click Events
        System::Void StudentProfileMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                StudentProfileForm^ studentProfileForm = gcnew StudentProfileForm(this->userID);
                studentProfileForm->MdiParent = this;
                studentProfileForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening student profile: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void EnrollmentMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                StudentEnrollmentForm^ enrollmentForm = gcnew StudentEnrollmentForm(userID);
                enrollmentForm->MdiParent = this;
                enrollmentForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening enrollment form: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void ViewGradesMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                StudentGradesForm^ gradesForm = gcnew StudentGradesForm(this->userID);
                gradesForm->MdiParent = this;
                gradesForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening grades form: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void ViewScheduleMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                StudentScheduleForm^ scheduleForm = gcnew StudentScheduleForm(this->userID);
                scheduleForm->MdiParent = this;
                scheduleForm->WindowState = FormWindowState::Maximized;
                scheduleForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening schedule: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void ViewTranscriptMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            TranscriptForm^ transcript = gcnew TranscriptForm(this->userID);
            transcript->MdiParent = this;
            transcript->Show();
        }

        System::Void FacultyProfileMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                FacultyProfileForm^ facultyProfileForm = gcnew FacultyProfileForm(this->userID);
                facultyProfileForm->MdiParent = this;
                facultyProfileForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening faculty profile: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void ManageCoursesMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                CourseManagementForm^ courseManagementForm = gcnew CourseManagementForm(this->userID);
                courseManagementForm->MdiParent = this;
                courseManagementForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening course management: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void EnterGradesMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                GradeEntryForm^ gradeEntryForm = gcnew GradeEntryForm(this->userID);
                gradeEntryForm->MdiParent = this;
                gradeEntryForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening grade entry: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void ViewRosterMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                ViewRosterForm^ rosterForm = gcnew ViewRosterForm(this->userID);
                rosterForm->MdiParent = this;
                rosterForm->Show();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening class roster: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void ManageProgramsMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            ManageProgramsForm^ adForm = gcnew ManageProgramsForm();
            adForm->MdiParent = this;
            adForm->Show();
        }

        System::Void ManageUsersMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            UserManagementForm^ manageUserForm = gcnew UserManagementForm();
            manageUserForm->MdiParent = this;
            manageUserForm->Show();
        }

        System::Void GenerateReportsMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            ReportGenerationForm^ reportForm = gcnew ReportGenerationForm();
            reportForm->MdiParent = this;
            reportForm->Show();
        }

        System::Void LogoutMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            if (MessageBox::Show("Are you sure you want to logout?", "Confirm Logout",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                Application::Restart();
            }
        }

        System::Void ExitMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            if (MessageBox::Show("Are you sure you want to exit?", "Confirm Exit",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                Application::Exit();
            }
        }

        System::Void AboutMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("University Management System\nVersion 1.0\n©2024", "About",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    };
}