#pragma once
#include "injection.h"
#include <string>
#include <msclr\marshal_cppstd.h>

namespace DllPieInjector {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ windowForm
	/// </summary>
	public ref class windowForm : public System::Windows::Forms::Form
	{
	private:
		Injector* injector;

	public:
		windowForm(void)
		{
			InitializeComponent();
			injector = new Injector();
			for (auto proc : injector->processes) {
				this->ProcessComboBox->Items->Add(gcnew String(proc.second.c_str()));
			}
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~windowForm()
		{
			delete injector;
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ComboBox^ InjectionMethodComboBox;
	private: System::Windows::Forms::ComboBox^ ProcessComboBox;
	private: System::Windows::Forms::Button^ InjectButton;
	private: System::Windows::Forms::CheckBox^ CloseAfterInjectionCheckBox;
	private: System::Windows::Forms::Button^ FileBrowseButton;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ PathToDllTextBox;
	private: System::Windows::Forms::CheckBox^ DelayCheckBox;
	private: System::Windows::Forms::NumericUpDown^ DelayNumericUpDown;



	
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(windowForm::typeid));
			this->InjectButton = (gcnew System::Windows::Forms::Button());
			this->InjectionMethodComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ProcessComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->CloseAfterInjectionCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->FileBrowseButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->PathToDllTextBox = (gcnew System::Windows::Forms::TextBox());
			this->DelayCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DelayNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DelayNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// InjectButton
			// 
			this->InjectButton->Location = System::Drawing::Point(11, 157);
			this->InjectButton->Name = L"InjectButton";
			this->InjectButton->Size = System::Drawing::Size(301, 52);
			this->InjectButton->TabIndex = 0;
			this->InjectButton->Text = L"Inject!";
			this->InjectButton->UseVisualStyleBackColor = true;
			this->InjectButton->Click += gcnew System::EventHandler(this, &windowForm::InjectButton_Click);
			// 
			// InjectionMethodComboBox
			// 
			this->InjectionMethodComboBox->FormattingEnabled = true;
			this->InjectionMethodComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"LoadLibraryA" });
			this->InjectionMethodComboBox->Location = System::Drawing::Point(13, 70);
			this->InjectionMethodComboBox->Name = L"InjectionMethodComboBox";
			this->InjectionMethodComboBox->Size = System::Drawing::Size(301, 24);
			this->InjectionMethodComboBox->Sorted = true;
			this->InjectionMethodComboBox->TabIndex = 1;
			this->InjectionMethodComboBox->Text = L"Injection Method";
			this->InjectionMethodComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &windowForm::InjectionMethodComboBox_SelectedIndexChanged);
			// 
			// ProcessComboBox
			// 
			this->ProcessComboBox->FormattingEnabled = true;
			this->ProcessComboBox->Location = System::Drawing::Point(11, 40);
			this->ProcessComboBox->Name = L"ProcessComboBox";
			this->ProcessComboBox->Size = System::Drawing::Size(301, 24);
			this->ProcessComboBox->TabIndex = 2;
			this->ProcessComboBox->Text = L"Process";
			this->ProcessComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &windowForm::ProcessComboBox_SelectedIndexChanged);
			// 
			// CloseAfterInjectionCheckBox
			// 
			this->CloseAfterInjectionCheckBox->AutoSize = true;
			this->CloseAfterInjectionCheckBox->Location = System::Drawing::Point(11, 130);
			this->CloseAfterInjectionCheckBox->Name = L"CloseAfterInjectionCheckBox";
			this->CloseAfterInjectionCheckBox->Size = System::Drawing::Size(154, 21);
			this->CloseAfterInjectionCheckBox->TabIndex = 3;
			this->CloseAfterInjectionCheckBox->Text = L"Close after injection";
			this->CloseAfterInjectionCheckBox->UseVisualStyleBackColor = true;
			// 
			// FileBrowseButton
			// 
			this->FileBrowseButton->Location = System::Drawing::Point(237, 11);
			this->FileBrowseButton->Name = L"FileBrowseButton";
			this->FileBrowseButton->Size = System::Drawing::Size(75, 23);
			this->FileBrowseButton->TabIndex = 4;
			this->FileBrowseButton->Text = L"Browse";
			this->FileBrowseButton->UseVisualStyleBackColor = true;
			this->FileBrowseButton->Click += gcnew System::EventHandler(this, &windowForm::FileBrowseButton_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"(*.dll)|*.dll";
			// 
			// PathToDllTextBox
			// 
			this->PathToDllTextBox->Location = System::Drawing::Point(11, 12);
			this->PathToDllTextBox->Name = L"PathToDllTextBox";
			this->PathToDllTextBox->ReadOnly = true;
			this->PathToDllTextBox->Size = System::Drawing::Size(220, 22);
			this->PathToDllTextBox->TabIndex = 5;
			this->PathToDllTextBox->Text = L"Path to dll";
			// 
			// DelayCheckBox
			// 
			this->DelayCheckBox->AutoSize = true;
			this->DelayCheckBox->Location = System::Drawing::Point(11, 103);
			this->DelayCheckBox->Name = L"DelayCheckBox";
			this->DelayCheckBox->Size = System::Drawing::Size(66, 21);
			this->DelayCheckBox->TabIndex = 6;
			this->DelayCheckBox->Text = L"Delay";
			this->DelayCheckBox->UseVisualStyleBackColor = true;
			this->DelayCheckBox->CheckedChanged += gcnew System::EventHandler(this, &windowForm::DelayCheckBox_CheckedChanged);
			// 
			// DelayNumericUpDown
			// 
			this->DelayNumericUpDown->Enabled = false;
			this->DelayNumericUpDown->Location = System::Drawing::Point(83, 102);
			this->DelayNumericUpDown->Name = L"DelayNumericUpDown";
			this->DelayNumericUpDown->Size = System::Drawing::Size(82, 22);
			this->DelayNumericUpDown->TabIndex = 7;
			// 
			// windowForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(326, 221);
			this->Controls->Add(this->DelayNumericUpDown);
			this->Controls->Add(this->DelayCheckBox);
			this->Controls->Add(this->PathToDllTextBox);
			this->Controls->Add(this->FileBrowseButton);
			this->Controls->Add(this->CloseAfterInjectionCheckBox);
			this->Controls->Add(this->ProcessComboBox);
			this->Controls->Add(this->InjectionMethodComboBox);
			this->Controls->Add(this->InjectButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"windowForm";
			this->Text = L"DllPie Injector";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DelayNumericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
private:
	
	System::Void ProcessComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void InjectionMethodComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void InjectButton_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void FileBrowseButton_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void DelayCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}
