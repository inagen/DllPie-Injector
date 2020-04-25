#include "windowForm.h"
#include <Windows.h>

using namespace DllPieInjector;


[System::STAThread]
int WINAPI  WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew windowForm);
	return 0;
}

System::Void windowForm::ProcessComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	auto ind = ProcessComboBox->SelectedIndex;
	injector->setProcessByIndex(ind);
}

System::Void windowForm::InjectionMethodComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	auto selectedInjectionMethod = (InjectionMethodComboBox->SelectedItem);
	if (selectedInjectionMethod == L"LoadLibraryA") {
		injector->setInjectionMethod(Injector::InjectionMethod::LoadLibraryA);
	}
}

System::Void windowForm::InjectButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Sleep((uint64_t)this->DelayNumericUpDown->Value * 1000);
	injector->inject();
	if (this->CloseAfterInjectionCheckBox->Checked) {
		exit(EXIT_SUCCESS);
	}
}
System::Void windowForm::FileBrowseButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->openFileDialog1->ShowDialog();
	this->PathToDllTextBox->Text = this->openFileDialog1->FileName;

	injector->setDllPath(msclr::interop::marshal_as< std::string >(this->PathToDllTextBox->Text));
}
System::Void windowForm::DelayCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (this->DelayCheckBox->Checked) {
		this->DelayNumericUpDown->Enabled = true;
	}
	else {
		this->DelayNumericUpDown->Enabled = false;
		this->DelayNumericUpDown->Value = 0;
	}
}

