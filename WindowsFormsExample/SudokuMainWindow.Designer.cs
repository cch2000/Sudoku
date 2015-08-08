using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace WindowsFormsExample
{
    partial class SudokuMainWindow
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

        private void On_changeButton_Click(object sender, System.EventArgs e)
        {
            List<int> numbers = SudukuGenerator.CreateNew();
            updateSudokuBoard(numbers);
            this.gameToSolve = String.Empty;
            this.Invalidate();
        }


        private void On_exportButton_Click(object sender, System.EventArgs e)
        {
            var saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            saveFileDialog.Title = "Export board to a file";
            saveFileDialog.Filter = "Sudoku Source files (*.sudoku)|*.txt|All files (*.*)|*.*";
            saveFileDialog.DefaultExt = ".sudoku";
            saveFileDialog.ShowDialog();
            DialogResult result = saveFileDialog.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string file = saveFileDialog.FileName;
                try
                {
                    string text = SudukuGenerator.ExportExisting(existingValues);
                    File.WriteAllText(file, text);
                }
                catch (Exception exp)
                {
                    MessageBox.Show(exp.Message, exp.GetType().Name);
                }
            }
        }

        private void On_importButton_Click(object sender, System.EventArgs e)
        {
            var openFileDialog = new System.Windows.Forms.OpenFileDialog();
            openFileDialog.Title = "Import a sudoku file";
            openFileDialog.Filter = "Sudoku Source files (*.sudoku)|*.txt|All files (*.*)|*.*";
            openFileDialog.DefaultExt = ".sudoku";
            DialogResult result = openFileDialog.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string file = openFileDialog.FileName;
                try
                {
                    string text = File.ReadAllText(file);
                    text = Regex.Replace(text, @"\s+|\t|\n|\r", "");
                    gameToSolve = text;
                    updateSudokuBoard(SudukuGenerator.ImportNew(text));
                    this.Invalidate();
                }
                catch (Exception exp)
                {
                    MessageBox.Show(exp.StackTrace, exp.GetType().Name);
                }
            }
        }

        private void On_solveButton_Click(object sender, System.EventArgs e)
        {
            if (!gameToSolve.Equals(String.Empty))
            {
                if (!SudokuSolver.hasASolution(gameToSolve))
                {
                    MessageBox.Show("No solution: \n" + gameToSolve, "Sorry!");
                    return;
                }
                var solution = SudokuSolver.solveGame(gameToSolve);
                updateSudokuBoard(SudukuGenerator.ImportNew(solution));
                gameToSolve = String.Empty;
            }
            else
            {
                MessageBox.Show("Game has already been solved", "Sorry!");
            }
        }

        private void On_infoButton_Click(object sender, System.EventArgs e)
        {
            if (!gameToSolve.Equals(String.Empty))
            {
                var level = SudokuSolver.getGameLevel(gameToSolve);
                var message = String.Format("Difficulty level: {0}.", this.levelMap[level]);
                MessageBox.Show(message, "Puzzle info");
            }
        }

        private void On_validateButton_Click(object sender, System.EventArgs e)
        {
            if (!gameToSolve.Equals(String.Empty))
            {
                var isUnique = SudokuSolver.hasASolution(gameToSolve);
                var message = String.Format("{0}", isUnique ? "This is a valid puzzle" : 
                                            @"This puzzle has more than one solution!!!\n Invalid");
                MessageBox.Show(message, "Validate Puzzle");
            }
        }

        private void createChangeButton()
        {
            this.changeButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.changeButton.Location = new System.Drawing.Point(480, 10);
            this.changeButton.Size = new System.Drawing.Size(100, 50);
            this.changeButton.Text = "Change";
            this.changeButton.BackColor = System.Drawing.Color.Silver;
            this.changeButton.Click += On_changeButton_Click;
            this.Controls.Add(this.changeButton);
        }
        private void createExportButton()
        {
            this.exportButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.exportButton.Location = new System.Drawing.Point(480, 70);
            this.exportButton.Size = new System.Drawing.Size(100, 50);
            this.exportButton.Text = "Export";
            this.exportButton.BackColor = System.Drawing.Color.Silver;
            this.exportButton.Click += On_exportButton_Click;
            this.Controls.Add(this.exportButton);
        }

        private void createImportButton()
        {
            this.importButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.importButton.Location = new System.Drawing.Point(480, 130);
            this.importButton.Size = new System.Drawing.Size(100, 50);
            this.importButton.Text = "Import...";
            this.importButton.BackColor = System.Drawing.Color.Silver;
            this.importButton.Click += On_importButton_Click;
            this.Controls.Add(this.importButton);
        }

        private void createSolveButton()
        {
            this.solveButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.solveButton.Location = new System.Drawing.Point(480, 190);
            this.solveButton.Size = new System.Drawing.Size(100, 50);
            this.solveButton.Text = "Solve!";
            this.solveButton.BackColor = System.Drawing.Color.Silver;
            this.solveButton.Click += On_solveButton_Click;
            this.Controls.Add(this.solveButton);
        }

        private void createInfoButton()
        {
            this.infoButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.infoButton.Location = new System.Drawing.Point(480, 250);
            this.infoButton.Size = new System.Drawing.Size(100, 50);
            this.infoButton.Text = "Info";
            this.infoButton.BackColor = System.Drawing.Color.Silver;
            this.infoButton.Click += On_infoButton_Click;
            this.Controls.Add(this.infoButton);
        }

        private void createValidateButton()
        {
            this.validateButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.validateButton.Location = new System.Drawing.Point(480, 310);
            this.validateButton.Size = new System.Drawing.Size(100, 50);
            this.validateButton.Text = "Validate!";
            this.validateButton.BackColor = System.Drawing.Color.Silver;
            this.validateButton.Click += On_validateButton_Click;
            this.Controls.Add(this.validateButton);
        }

        private void updateSudokuBoard(List<int> input)
        {
            for (int i = 0; i < 81; i++)
            {
                NumberBlocks[i].Text = input[i].ToString();
                if (input[i] == 0)
                {
                    NumberBlocks[i].BackColor = colorMap[0];
                    NumberBlocks[i].ForeColor = colorMap[0];
                }
                else
                {
                    NumberBlocks[i].ForeColor = System.Drawing.Color.Black;
                    NumberBlocks[i].BackColor = colorMap[input[i]];
                }
            }
            existingValues = input;
        }
   
        private void createSudokuBoard(List<int> input)
        {
            this.NumberBlocks = new List<System.Windows.Forms.Label>();
            for (int i = 0; i < 81; i++)
            {

                var block = new System.Windows.Forms.Label();
                int row = i / 9;
                int col = i % 9;
                var blockName = string.Format("block{0}{1}", row, col);
                this.SuspendLayout();
                block.AutoSize = true;
                block.ImageIndex = i;
                block.Location = new System.Drawing.Point(row * 50, col * 50);
                block.Name = blockName;
                block.Size = new System.Drawing.Size(50, 50);
                block.Font = new System.Drawing.Font(System.Drawing.FontFamily.GenericSansSerif, 32);
                block.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
                block.TabIndex = i;
                if (input[i] == 0)
                {
                    block.BackColor = colorMap[0];
                    block.ForeColor = colorMap[0];
                }
                else
                {
                    block.ForeColor = System.Drawing.Color.Black;
                    block.BackColor = colorMap[input[i]];
                }
                block.Text = input[i].ToString();
                this.NumberBlocks.Add(block);
                this.Controls.Add(block);
            }
        }
        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {

            // 
            // SudokuMainWindow
            //
            List<int> numbers = SudukuGenerator.CreateNew();
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 500);
            this.Name = "SudokuMainWindow";
            this.Text = "Sudoku";
            this.ResumeLayout(false);
            createSudokuBoard(numbers);
            createChangeButton();
            createExportButton();
            createImportButton();
            createSolveButton();
            createInfoButton();
            createValidateButton();
            this.PerformLayout();
            this.existingValues = numbers;
        }

        #endregion

        private List<Label> NumberBlocks;
        private Button changeButton;
        private Button exportButton;
        private Button importButton;
        private Button solveButton;
        private Button infoButton;
        private Button validateButton;

        private List<int> existingValues;
        private String gameToSolve;
        private readonly Dictionary<int, String> levelMap = new Dictionary<int, String>
        {
            {0, "Easy"},
            {1, "Medium"},
            {2, "Hard"},
            {3, "Samurai"},
            {4, "Invalid puzzle" }
        };
        private readonly Dictionary<int, System.Drawing.Color> colorMap = new Dictionary<int, System.Drawing.Color>
        {
            {0,  System.Drawing.Color.White},
            {1,  System.Drawing.Color.Violet},
            {2, System.Drawing.Color.Aqua },
            { 3, System.Drawing.Color.Coral},
            { 4, System.Drawing.Color.DarkCyan},
            { 5, System.Drawing.Color.Olive},
            { 6, System.Drawing.Color.Orange},
            { 7, System.Drawing.Color.Pink},
            { 8, System.Drawing.Color.YellowGreen},
            { 9, System.Drawing.Color.Wheat}
        };
    }
}

