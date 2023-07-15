#include <iostream>
#include <string>

using namespace std;

// Function to find the One's complement
// of the given binary string
string Ones_complement(string data)
{
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '0')
            data[i] = '1';
        else
            data[i] = '0';
    }
    return data;
}

// Function to return the checksum value of
// the given string when divided in K size blocks
string checkSum(string data, int block_size)
{
    // Check data size is divisible by block_size
    // Otherwise add '0' front of the data
    int n = data.length();
    if (n % block_size != 0) {
        int pad_size = block_size - (n % block_size);
        for (int i = 0; i < pad_size; i++) {
            data = '0' + data;
        }
    }

    // Binary addition of all blocks with carry
    string result = "";

    // First block of data stored in result variable
    for (int i = 0; i < block_size; i++) {
        result += data[i];
    }

    // Loop to calculate the block
    // wise addition of data
    for (int i = block_size; i < n; i += block_size) {

        // Stores the data of the next block
        string next_block = "";

        for (int j = i; j < i + block_size; j++) {
            next_block += data[j];
        }

        // Stores the binary addition of two blocks
        string additions = "";
        int sum = 0, carry = 0;

        // Loop to calculate the binary addition of
        // the current two blocls of k size
        for (int k = block_size - 1; k >= 0; k--) {
            sum += (next_block[k] - '0')
                + (result[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                additions = '0' + additions;
                sum = carry;
            }
            else if (sum == 1) {
                additions = '1' + additions;
                sum = carry;
            }
            else if (sum == 2) {
                additions = '0' + additions;
                sum = carry;
            }
            else {
                additions = '1' + additions;
                sum = carry;
            }
        }

        // After binary add of two blocks with carry,
        // if carry is 1 then apply binary addition
        string final = "";

        if (carry == 1) {
            for (int l = additions.length() - 1; l >= 0;
                l--) {
                if (carry == 0) {
                    final = additions[l] + final;
                }
                else if (((additions[l] - '0') + carry) % 2
                        == 0) {
                    final = "0" + final;
                    carry = 1;
                }
                else {
                    final = "1" + final;
                    carry = 0;
                }
            }

            result = final;
        }
        else {
            result = additions;
        }
    }

    // Return One's complements of result value
    // which represents the required checksum value
    return Ones_complement(result);
}

bool verifyCheckSum(string data, string checksum, int block_size) {
    // Check data size is divisible by block_size
    // Otherwise add '0' front of the data
    int n = data.length();
    if (n % block_size != 0) {
        int pad_size = block_size - (n % block_size);
        for (int i = 0; i < pad_size; i++) {
            data = '0' + data;
        }
        n = data.length();
    }

    // Binary addition of all blocks with carry
    string result = "";

    // First block of data stored in result variable
    for (int i = 0; i < block_size; i++) {
        result += data[i];
    }

    // Loop to calculate the block
    // wise addition of data
    for (int i = block_size; i < n; i += block_size) {

        // Stores the data of the next block
        string next_block = "";

        for (int j = i; j < i + block_size; j++) {
            next_block += data[j];
        }

        // Stores the binary addition of two blocks
        string additions = "";
        int sum = 0, carry = 0;

        // Loop to calculate the binary addition of
        // the current two blocks of k size
        for (int k = block_size - 1; k >= 0; k--) {
            sum += (next_block[k] - '0')
                + (result[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                additions = '0' + additions;
                sum = carry;
            }
            else if (sum == 1) {
                additions = '1' + additions;
                sum = carry;
            }
            else if (sum == 2) {
                additions = '0' + additions;
                sum = carry;
            }
            else {
                additions = '1' + additions;
                sum = carry;
            }
        }

        // After binary add of two blocks with carry,
        // if carry is 1 then apply binary addition
        string final = "";

        if (carry == 1) {
            for (int l = additions.length() - 1; l >= 0;
                l--) {
                if (carry == 0) {
                    final = additions[l] + final;
                }
                else if (((additions[l] - '0') + carry) % 2
                        == 0) {
                    final = "0" + final;
                    carry = 1;
                }
                else {
                    final = "1" + final;
                    carry = 0;
                }
            }

            result = final;
        }
        else {
            result = additions;
        }
    }

    // Return One's complements of result value
    // which represents the calculated checksum value
    string calculated_checksum = Ones_complement(result);

    // Compare the calculated checksum value with the given checksum
    return calculated_checksum == checksum;
}

int main() {
    string data = "1101011011101101";
    int block_size = 4;

    // Calculate the checksum value of the data
    string checksum = checkSum(data, block_size);
    cout << "Checksum value: " << checksum << endl;

    // Verify the checksum value of the data
    bool isValid = verifyCheckSum(data, checksum, block_size);
    if (isValid) {
        cout << "Checksum verification successful" << endl;
    } else {
        cout << "Checksum verification failed" << endl;
    }

    return 0;
}

