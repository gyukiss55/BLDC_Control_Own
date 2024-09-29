using System;
using System.IO.Ports;
using System.Diagnostics;
using System.Windows.Forms;
using System.ComponentModel.Design;
using System.IO;


namespace Win32UARTControl
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.ResetButton = new System.Windows.Forms.Button();
            this.UARTButton = new System.Windows.Forms.Button();
            this.UARTNameText = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.PeriodBar = new System.Windows.Forms.TrackBar();
            this.PulseBar = new System.Windows.Forms.TrackBar();
            this.PeriodTimeText = new System.Windows.Forms.TextBox();
            this.PulseTimeText = new System.Windows.Forms.TextBox();
            this.SaveButton = new System.Windows.Forms.Button();
            this.ExitButton = new System.Windows.Forms.Button();
            this.Log1Text = new System.Windows.Forms.TextBox();
            this.Log2Text = new System.Windows.Forms.TextBox();
            this.Log3Text = new System.Windows.Forms.TextBox();
            this.Log4Text = new System.Windows.Forms.TextBox();
            this.Log5Text = new System.Windows.Forms.TextBox();
            this.SendButton = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.UARTStatusCheckBox = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.CycleNumberText = new System.Windows.Forms.TextBox();
            this.cyles = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.PeriodBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PulseBar)).BeginInit();
            this.SuspendLayout();
            // 
            // ResetButton
            // 
            this.ResetButton.Location = new System.Drawing.Point(135, 330);
            this.ResetButton.Name = "ResetButton";
            this.ResetButton.Size = new System.Drawing.Size(75, 23);
            this.ResetButton.TabIndex = 9;
            this.ResetButton.Text = "Reset";
            this.ResetButton.UseVisualStyleBackColor = true;
            // 
            // UARTButton
            // 
            this.UARTButton.Location = new System.Drawing.Point(382, 28);
            this.UARTButton.Name = "UARTButton";
            this.UARTButton.Size = new System.Drawing.Size(75, 23);
            this.UARTButton.TabIndex = 1;
            this.UARTButton.Text = "Set UART";
            this.UARTButton.UseVisualStyleBackColor = true;
            // 
            // UARTNameText
            // 
            this.UARTNameText.Location = new System.Drawing.Point(473, 30);
            this.UARTNameText.Name = "UARTNameText";
            this.UARTNameText.Size = new System.Drawing.Size(100, 20);
            this.UARTNameText.TabIndex = 2;
            this.UARTNameText.Text = "COM18";
            // 
            // PeriodBar
            // 
            this.PeriodBar.Location = new System.Drawing.Point(20, 70);
            this.PeriodBar.Maximum = 20;
            this.PeriodBar.Minimum = 1;
            this.PeriodBar.Name = "PeriodBar";
            this.PeriodBar.Size = new System.Drawing.Size(437, 45);
            this.PeriodBar.TabIndex = 4;
            this.PeriodBar.Value = 20;
            // 
            // PulseBar
            // 
            this.PulseBar.LargeChange = 10;
            this.PulseBar.Location = new System.Drawing.Point(20, 104);
            this.PulseBar.Maximum = 100;
            this.PulseBar.Name = "PulseBar";
            this.PulseBar.Size = new System.Drawing.Size(437, 45);
            this.PulseBar.TabIndex = 5;
            // 
            // PeriodTimeText
            // 
            this.PeriodTimeText.Enabled = false;
            this.PeriodTimeText.Location = new System.Drawing.Point(473, 75);
            this.PeriodTimeText.Name = "PeriodTimeText";
            this.PeriodTimeText.Size = new System.Drawing.Size(100, 20);
            this.PeriodTimeText.TabIndex = 5;
            this.PeriodTimeText.Text = "20";
            // 
            // PulseTimeText
            // 
            this.PulseTimeText.Enabled = false;
            this.PulseTimeText.Location = new System.Drawing.Point(474, 105);
            this.PulseTimeText.Name = "PulseTimeText";
            this.PulseTimeText.Size = new System.Drawing.Size(100, 20);
            this.PulseTimeText.TabIndex = 6;
            this.PulseTimeText.Text = "0";
            // 
            // SaveButton
            // 
            this.SaveButton.Location = new System.Drawing.Point(21, 330);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(75, 23);
            this.SaveButton.TabIndex = 7;
            this.SaveButton.Text = "Save";
            this.SaveButton.UseVisualStyleBackColor = true;
            // 
            // ExitButton
            // 
            this.ExitButton.Location = new System.Drawing.Point(498, 330);
            this.ExitButton.Name = "ExitButton";
            this.ExitButton.Size = new System.Drawing.Size(75, 23);
            this.ExitButton.TabIndex = 8;
            this.ExitButton.Text = "Exit";
            this.ExitButton.UseVisualStyleBackColor = true;
            // 
            // Log1Text
            // 
            this.Log1Text.Location = new System.Drawing.Point(20, 182);
            this.Log1Text.Name = "Log1Text";
            this.Log1Text.Size = new System.Drawing.Size(554, 20);
            this.Log1Text.TabIndex = 101;
            this.Log1Text.TabStop = false;
            // 
            // Log2Text
            // 
            this.Log2Text.Location = new System.Drawing.Point(21, 208);
            this.Log2Text.Name = "Log2Text";
            this.Log2Text.Size = new System.Drawing.Size(554, 20);
            this.Log2Text.TabIndex = 102;
            this.Log2Text.TabStop = false;
            // 
            // Log3Text
            // 
            this.Log3Text.Location = new System.Drawing.Point(21, 234);
            this.Log3Text.Name = "Log3Text";
            this.Log3Text.Size = new System.Drawing.Size(554, 20);
            this.Log3Text.TabIndex = 103;
            this.Log3Text.TabStop = false;
            // 
            // Log4Text
            // 
            this.Log4Text.Location = new System.Drawing.Point(21, 260);
            this.Log4Text.Name = "Log4Text";
            this.Log4Text.Size = new System.Drawing.Size(554, 20);
            this.Log4Text.TabIndex = 104;
            this.Log4Text.TabStop = false;
            // 
            // Log5Text
            // 
            this.Log5Text.Location = new System.Drawing.Point(20, 286);
            this.Log5Text.Name = "Log5Text";
            this.Log5Text.Size = new System.Drawing.Size(554, 20);
            this.Log5Text.TabIndex = 105;
            this.Log5Text.TabStop = false;
            // 
            // SendButton
            // 
            this.SendButton.Location = new System.Drawing.Point(32, 27);
            this.SendButton.Name = "SendButton";
            this.SendButton.Size = new System.Drawing.Size(75, 23);
            this.SendButton.TabIndex = 3;
            this.SendButton.Text = "Send";
            this.SendButton.UseVisualStyleBackColor = true;
            // 
            // UARTStatusCheckBox
            // 
            this.UARTStatusCheckBox.AutoSize = true;
            this.UARTStatusCheckBox.Enabled = false;
            this.UARTStatusCheckBox.Location = new System.Drawing.Point(591, 33);
            this.UARTStatusCheckBox.Name = "UARTStatusCheckBox";
            this.UARTStatusCheckBox.Size = new System.Drawing.Size(54, 17);
            this.UARTStatusCheckBox.TabIndex = 107;
            this.UARTStatusCheckBox.TabStop = false;
            this.UARTStatusCheckBox.Text = "status";
            this.UARTStatusCheckBox.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(591, 78);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 108;
            this.label1.Text = "milli sec";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(588, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(15, 13);
            this.label2.TabIndex = 109;
            this.label2.Text = "%";
            // 
            // CycleNumberText
            // 
            this.CycleNumberText.Location = new System.Drawing.Point(473, 136);
            this.CycleNumberText.Name = "CycleNumberText";
            this.CycleNumberText.Size = new System.Drawing.Size(100, 20);
            this.CycleNumberText.TabIndex = 110;
            this.CycleNumberText.Text = "10";
            // 
            // cyles
            // 
            this.cyles.AutoSize = true;
            this.cyles.Location = new System.Drawing.Point(591, 139);
            this.cyles.Name = "cyles";
            this.cyles.Size = new System.Drawing.Size(31, 13);
            this.cyles.TabIndex = 111;
            this.cyles.Text = "cyles";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(659, 373);
            this.Controls.Add(this.cyles);
            this.Controls.Add(this.CycleNumberText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.UARTStatusCheckBox);
            this.Controls.Add(this.SendButton);
            this.Controls.Add(this.Log5Text);
            this.Controls.Add(this.Log4Text);
            this.Controls.Add(this.Log3Text);
            this.Controls.Add(this.Log2Text);
            this.Controls.Add(this.Log1Text);
            this.Controls.Add(this.ExitButton);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.PulseTimeText);
            this.Controls.Add(this.PeriodTimeText);
            this.Controls.Add(this.PulseBar);
            this.Controls.Add(this.PeriodBar);
            this.Controls.Add(this.UARTNameText);
            this.Controls.Add(this.UARTButton);
            this.Controls.Add(this.ResetButton);
            this.KeyPreview = true;
            this.Name = "Form1";
            this.Text = "Serial Control";
            ((System.ComponentModel.ISupportInitialize)(this.PeriodBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PulseBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ResetButton;
        private System.Windows.Forms.Button UARTButton;
        private System.Windows.Forms.TextBox UARTNameText;
        private System.Windows.Forms.TrackBar PeriodBar;
        private System.Windows.Forms.TrackBar PulseBar;
        private System.Windows.Forms.TextBox PeriodTimeText;
        private System.Windows.Forms.TextBox PulseTimeText;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.Button ExitButton;
        private System.Windows.Forms.TextBox Log1Text;
        private System.Windows.Forms.TextBox Log2Text;
        private System.Windows.Forms.TextBox Log3Text;
        private System.Windows.Forms.TextBox Log4Text;
        private System.Windows.Forms.TextBox Log5Text;
        private System.Windows.Forms.Button SendButton;
        private System.Windows.Forms.CheckBox UARTStatusCheckBox;

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;

        private bool serialPortOpen = false ;

        private const int PeriodBarDefaultValue = 20;
        private const int PulseBarDefaultValue = 0;

        private string logFilePath = "..\\..\\..\\log\\BLDCControlLog.txt";

        private void HandleSubcomponenets ()
        {
            UARTButton.Click += UARTButton_Click;
            SendButton.Click += SendButton_Click;
            ResetButton.Click += ResetButton_Click;
            SaveButton.Click += SaveButton_Click;
            ExitButton.Click += ExitButton_Click;

            PeriodBar.ValueChanged += PeriodBar_ValueChanged;
            PulseBar.ValueChanged += PulseBar_ValueChanged;

            timer1.Tick += Timer1_Tick1;

            this.KeyDown += new KeyEventHandler(Form1_KeyDown);
        }

        private void Timer1_Tick1(object sender, EventArgs e)
        {
            if (serialPortOpen)
            {
                if (serialPort1.BytesToRead > 0)
                {
                    //string documentsPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
                    //Debug.WriteLine(documentsPath);
                    // Open a StreamWriter in append mode
                    using (StreamWriter writer = new StreamWriter(logFilePath, true))
                    {
                        while (serialPort1.BytesToRead > 0)
                        {
                            string log1 = serialPort1.ReadLine();
                            writer.WriteLine(log1);
                            AddLog(log1);
                        }
                    }
                }
            }
        }

        private void AddLog (string log)
        {
            Log5Text.Text = Log4Text.Text;
            Log4Text.Text = Log3Text.Text;
            Log3Text.Text = Log2Text.Text;
            Log2Text.Text = Log1Text.Text;
            Log1Text.Text = log;
        }

        private void PeriodBar_ValueChanged(object sender, EventArgs e)
        {
            int sliderValue = PeriodBar.Value;
            PeriodTimeText.Text = $"{sliderValue}";  // Update the label with the current slider value
        }

        private void UARTButton_Click (object sender, EventArgs e)
        {
            OpenSerialPort();
        }

        private void SendCommand ()
        {
            if (serialPortOpen)
            {
                string periodTxt = PeriodTimeText.Text;
                try
                {
                    int period = Convert.ToInt32(PeriodTimeText.Text);
                    int percent = Convert.ToInt32(PulseTimeText.Text);
                    int cycle = Convert.ToInt32(CycleNumberText.Text);
                    int pulse = percent * 10 * period;
                    period = period * 1000;
                    string command = "PPN:" + period.ToString() + "," + pulse.ToString() + "," + cycle.ToString();
                    Debug.WriteLine($"Command:{command}");

                    serialPort1.WriteLine(command);

                } 
                catch (FormatException ex)
                {
                    Debug.WriteLine(ex.Message);
                }
            }
        }
        private void SendButton_Click(object sender, EventArgs e)
        {
            SendCommand();
        }

        private void ResetButton_Click(object sender, EventArgs e)
        {
            PeriodBar.Value = PeriodBarDefaultValue;
            PulseBar.Value = PulseBarDefaultValue;
            SendCommand();
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            
        }

        private void ExitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void PulseBar_ValueChanged(object sender, EventArgs e)
        {
            int sliderValue = PulseBar.Value;
            PulseTimeText.Text = $"{sliderValue}";  // Update the label with the current slider value
            //throw new NotImplementedException();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            // Check if the F1 key is pressed
            if (e.KeyCode == Keys.F1)
            {
                SendCommand();
            }
        }


        bool OpenSerialPort ()
        {
            if (serialPortOpen)
            {
                serialPort1.Close();
                serialPortOpen = false;
            }

            serialPort1.PortName = UARTNameText.Text;
            serialPort1.BaudRate = 115200;
            serialPort1.DataBits = 8;
            serialPort1.Parity = Parity.None;
            serialPort1.StopBits = StopBits.One;
            serialPort1.Handshake = Handshake.None;
            try
            {
                serialPort1.Open();
                serialPortOpen = true;

                timer1.Interval = 100;
                timer1.Enabled = true;
                UARTStatusCheckBox.Checked = true;
                return true;
            }
            catch (System.IO.IOException ex)
            {
                Debug.WriteLine($"Error: {ex.Message}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error: {ex.Message}");
            }
            return false;
        }

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private TextBox CycleNumberText;
        private Label cyles;
    }

}

