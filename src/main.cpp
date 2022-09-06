#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void shift_seam(int ***rgb, int H, int W, int hv)
{
    int i, j, idx;
    if (hv == 1)
    {
        for (i = 0; i < H; i++)
        {
            idx = 0;
            for (j = 0; j < W; j++)
            {
                if (rgb[i][j][0] == -1)
                {
                    idx = j;
                    break;
                }
            }
            if (idx != W - 1)
            {
                while (idx != W - 2)
                {
                    rgb[i][idx][0] = rgb[i][idx + 1][0];
                    rgb[i][idx][1] = rgb[i][idx + 1][1];
                    rgb[i][idx][2] = rgb[i][idx + 1][2];
                    idx++;
                }
            }
        }
    }
    else
    {
        for (j = 0; j < W; j++)
        {
            idx = 0;
            for (i = 0; i < H; i++)
            {
                if (rgb[i][j][0] == -1)
                {
                    idx = i;
                    break;
                }
            }
            if (idx != H - 1)
            {
                while (idx != H - 2)
                {
                    rgb[idx][j][0] = rgb[idx + 1][j][0];
                    rgb[idx][j][1] = rgb[idx + 1][j][1];
                    rgb[idx][j][2] = rgb[idx + 1][j][2];
                    idx++;
                }
            }
        }
    }
}

void find_seam(int ***rgb, float **matrix, int H, int W, int hv)
{
    int i, j;

    if (hv == 1)
    {
        int idx_j = 0;

        for (j = 1; j < W; j++)
        {
            if (matrix[H - 1][j] < matrix[H - 1][idx_j])
            {
                idx_j = j;
            }
        }

        rgb[H - 1][idx_j][0] = -1;

        for (i = H - 2; i >= 0; i--)
        {
            if (idx_j == 0)
            {
                if (matrix[i][idx_j] < matrix[i][idx_j + 1])
                {
                    idx_j = idx_j;
                }
                else
                {
                    idx_j = idx_j + 1;
                }
            }
            else if (idx_j == W - 1)
            {
                if (matrix[i][idx_j] < matrix[i][idx_j - 1])
                {
                    idx_j = idx_j;
                }
                else
                {
                    idx_j = idx_j - 1;
                }
            }
            else
            {
                idx_j = idx_j - 1;
                for (j = 1; j < 3; j++)
                {
                    if (matrix[i][idx_j + j] < matrix[i][idx_j])
                    {
                        idx_j = idx_j + j;
                    }
                }
            }
            rgb[i][idx_j][0] = -1;
        }
    }
    else
    {
        int idx_i = 0;

        for (i = 1; i < H; i++)
        {
            if (matrix[i][W - 1] < matrix[idx_i][W - 1])
            {
                idx_i = i;
            }
        }

        rgb[idx_i][W - 1][0] = -1;

        for (j = W - 2; j >= 0; j--)
        {
            if (idx_i == 0)
            {
                if (matrix[idx_i][j] < matrix[idx_i + 1][j])
                {
                    idx_i = idx_i;
                }
                else
                {
                    idx_i = idx_i + 1;
                }
            }
            else if (idx_i == H - 1)
            {
                if (matrix[idx_i][j] < matrix[idx_i - 1][j])
                {
                    idx_i = idx_i;
                }
                else
                {
                    idx_i = idx_i - 1;
                }
            }
            else
            {
                idx_i = idx_i - 1;
                for (i = 1; i < 3; i++)
                {
                    if (matrix[idx_i + i][j] < matrix[idx_i][j])
                    {
                        idx_i = idx_i + i;
                    }
                }
            }
            rgb[idx_i][j][0] = -1;
        }
    }
}

void dp(float **matrix, int H, int W, int hv)
{
    if (hv == 1)
    {
        for (int i = 1; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (j == 0)
                {
                    matrix[i][j] += min(matrix[i - 1][j], matrix[i - 1][j + 1]);
                }
                else if (j == W - 1)
                {
                    matrix[i][j] += min(matrix[i - 1][j], matrix[i - 1][j - 1]);
                }
                else
                {
                    matrix[i][j] += min(min(matrix[i - 1][j], matrix[i - 1][j - 1]), matrix[i - 1][j + 1]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < H; i++)
        {
            for (int j = 1; j < W; j++)
            {
                if (i == 0)
                {
                    matrix[i][j] += min(matrix[i][j - 1], matrix[i + 1][j - 1]);
                }
                else if (i == H - 1)
                {
                    matrix[i][j] += min(matrix[i][j - 1], matrix[i - 1][j - 1]);
                }
                else
                {
                    matrix[i][j] += min(min(matrix[i][j - 1], matrix[i - 1][j - 1]), matrix[i + 1][j - 1]);
                }
            }
        }
    }
}

void calculate_energy_matrix(int ***rgb, float **matrix, int H, int W)
{

    int temp1, temp2, temp3, tempsum;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    temp1 = abs(rgb[i][j + 1][0] - rgb[i][W - 1][0]);
                    temp2 = abs(rgb[i][j + 1][1] - rgb[i][W - 1][1]);
                    temp3 = abs(rgb[i][j + 1][2] - rgb[i][W - 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[H - 1][j][0] - rgb[i + 1][j][0]);
                    temp2 = abs(rgb[H - 1][j][1] - rgb[i + 1][j][1]);
                    temp3 = abs(rgb[H - 1][j][2] - rgb[i + 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
                else if (j == W - 1)
                {
                    temp1 = abs(rgb[i][j - 1][0] - rgb[i][0][0]);
                    temp2 = abs(rgb[i][j - 1][1] - rgb[i][0][1]);
                    temp3 = abs(rgb[i][j - 1][2] - rgb[i][0][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[H - 1][j][0] - rgb[i + 1][j][0]);
                    temp2 = abs(rgb[H - 1][j][1] - rgb[i + 1][j][1]);
                    temp3 = abs(rgb[H - 1][j][2] - rgb[i + 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
                else
                {
                    temp1 = abs(rgb[i][j - 1][0] - rgb[i][j + 1][0]);
                    temp2 = abs(rgb[i][j - 1][1] - rgb[i][j + 1][1]);
                    temp3 = abs(rgb[i][j - 1][2] - rgb[i][j + 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[H - 1][j][0] - rgb[i + 1][j][0]);
                    temp2 = abs(rgb[H - 1][j][1] - rgb[i + 1][j][1]);
                    temp3 = abs(rgb[H - 1][j][2] - rgb[i + 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
            }
            else if (i == H - 1)
            {
                if (j == 0)
                {
                    temp1 = abs(rgb[i][W - 1][0] - rgb[i][j + 1][0]);
                    temp2 = abs(rgb[i][W - 1][1] - rgb[i][j + 1][1]);
                    temp3 = abs(rgb[i][W - 1][2] - rgb[i][j + 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[0][j][0] - rgb[i - 1][j][0]);
                    temp2 = abs(rgb[0][j][1] - rgb[i - 1][j][1]);
                    temp3 = abs(rgb[0][j][2] - rgb[i - 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
                else if (j == W - 1)
                {
                    temp1 = abs(rgb[i][j - 1][0] - rgb[i][0][0]);
                    temp2 = abs(rgb[i][j - 1][1] - rgb[i][0][1]);
                    temp3 = abs(rgb[i][j - 1][2] - rgb[i][0][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[0][j][0] - rgb[i - 1][j][0]);
                    temp2 = abs(rgb[0][j][1] - rgb[i - 1][j][1]);
                    temp3 = abs(rgb[0][j][2] - rgb[i - 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
                else
                {
                    temp1 = abs(rgb[i][j - 1][0] - rgb[i][j + 1][0]);
                    temp2 = abs(rgb[i][j - 1][1] - rgb[i][j + 1][1]);
                    temp3 = abs(rgb[i][j - 1][2] - rgb[i][j + 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[0][j][0] - rgb[i - 1][j][0]);
                    temp2 = abs(rgb[0][j][1] - rgb[i - 1][j][1]);
                    temp3 = abs(rgb[0][j][2] - rgb[i - 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
            }
            else
            {
                if (j == 0)
                {
                    temp1 = abs(rgb[i][W - 1][0] - rgb[i][j + 1][0]);
                    temp2 = abs(rgb[i][W - 1][1] - rgb[i][j + 1][1]);
                    temp3 = abs(rgb[i][W - 1][2] - rgb[i][j + 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[i + 1][j][0] - rgb[i - 1][j][0]);
                    temp2 = abs(rgb[i + 1][j][1] - rgb[i - 1][j][1]);
                    temp3 = abs(rgb[i + 1][j][2] - rgb[i - 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
                else if (j == W - 1)
                {
                    temp1 = abs(rgb[i][0][0] - rgb[i][j - 1][0]);
                    temp2 = abs(rgb[i][0][1] - rgb[i][j - 1][1]);
                    temp3 = abs(rgb[i][0][2] - rgb[i][j - 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[i + 1][j][0] - rgb[i - 1][j][0]);
                    temp2 = abs(rgb[i + 1][j][1] - rgb[i - 1][j][1]);
                    temp3 = abs(rgb[i + 1][j][2] - rgb[i - 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
                else
                {
                    temp1 = abs(rgb[i][j - 1][0] - rgb[i][j + 1][0]);
                    temp2 = abs(rgb[i][j - 1][1] - rgb[i][j + 1][1]);
                    temp3 = abs(rgb[i][j - 1][2] - rgb[i][j + 1][2]);
                    tempsum = pow((temp1 + temp2 + temp3), 2);

                    temp1 = abs(rgb[i + 1][j][0] - rgb[i - 1][j][0]);
                    temp2 = abs(rgb[i + 1][j][1] - rgb[i - 1][j][1]);
                    temp3 = abs(rgb[i + 1][j][2] - rgb[i - 1][j][2]);
                    tempsum += pow((temp1 + temp2 + temp3), 2);

                    matrix[i][j] = sqrt(tempsum);
                }
            }
        }
    }
}

void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_)
{
    // We've provided you the driver.py and main.cpp for your convinience
    // Please go through them and understand the file handling and input/output format
    // Feel free to experiment on your own

    // can access the array using rgb[i][j][k] like a regular 3D array

    // Write your code here
    float **energy_matrix;
    energy_matrix = new float *[H];
    for (int i = 0; i < H; i++)
    {
        energy_matrix[i] = new float[W];
    }

    while (W != W_)
    {
        calculate_energy_matrix(rgb, energy_matrix, H, W);
        dp(energy_matrix, H, W, 1);
        find_seam(rgb, energy_matrix, H, W, 1);
        shift_seam(rgb, H, W, 1);
        W = W - 1;
        // cout << "W: " << W << endl;
    }
    // cout << "1" << endl;
    while (H != H_)
    {
        calculate_energy_matrix(rgb, energy_matrix, H, W);
        dp(energy_matrix, H, W, 2);
        find_seam(rgb, energy_matrix, H, W, 2);
        shift_seam(rgb, H, W, 2);
        H = H - 1;
        // cout << "H: " << H << endl;
    }
}

int main()
{
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for (int i = 0; i < H; ++i)
    {
        rgb[i] = new int *[W];
        for (int j = 0; j < W; ++j)
        {
            rgb[i][j] = new int[C];
            for (int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;

    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);

    fout << H_ << " " << W_ << " " << C_ << endl;
    for (int i = 0; i < H_; ++i)
    {
        for (int j = 0; j < W_; ++j)
        {
            for (int k = 0; k < C_; ++k)
            {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}
