using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsExample
{
    class SudukuGenerator
    {
        private static List<int> board = new List<int>();
        private static bool isSafe(int row, int col, int value)
        {
            for(int i = 0; i < row; i++)
            {
                if (board[i * 9 + col] == value)
                    return false;
            }

            for(int j = 0; j < col; j++)
            {
                if (board[row * 9 + j] == value)
                    return false;
            }

            int base_row = row / 3 * 3;
            int base_col = col / 3 * 3;
            for(int m = base_row; m <= row; m++)
            {
                for(int n = base_col; n <= col; n++)
                {
                    // The new value doesn't exist yet
                    if (m == row && n == col)
                        break;
                    if (board[m * 9 + n] == value)
                        return false;
                }
            }
            return true;
        }
        public static List<int> CreateNew()
        {
            int[] origin = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            Random r = new Random();
            for (int i = 0; i < 9; i++)
            {
                for(int j = i; j < 9; j++)
                {
                    int index = r.Next(i, 9);
                    var temp = origin[i];
                    origin[i] = origin[index];
                    origin[index] = temp;
                }
            }
            board.AddRange(origin);
            for (int i = 0; i < 72; i++)
                board.Add(0);
            for(int k = 9; k < 81;)
            {
                var found = false;
                var value = board[k];
                value++;
                while(!found && value <= 9)
                {
                    int row = k / 9;
                    int col = k % 9;
                    if (isSafe(row, col, value))
                    {
                        board[k] = value;
                        k++;
                        found = true;
                    } else
                    {
                        value++;
                    }

                }
                if (!found)
                {
                    board[k] = 0;
                    k--;
                }
            }
            return board;
        }
        public static List<int> ImportNew(string text)
        {
            return text.ToCharArray().Select(c => char.IsDigit(c) ? int.Parse(Char.ToString(c)) : 0).ToList();
        }
        public static string ExportExisting(List<int> numbers)
        {
            return numbers.Select(n => n != 0 ? char.Parse(n.ToString()) : '-').ToString();
        }
         
    }
}
