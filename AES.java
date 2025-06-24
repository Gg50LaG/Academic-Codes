import java.util.Scanner;
public class AES {
private static String toHex(String input) {
StringBuilder hexString = new StringBuilder();
for (char ch : input.toCharArray()) {
hexString.append(String.format("%02X", (int) ch));
}
return hexString.toString();
}
private static final int[][] S_BOX = {
{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};
public static String xorHexStrings(String hex1, String hex2) {
StringBuilder result = new StringBuilder();
for (int i = 0; i < hex1.length(); i += 2) {
int val1 = Integer.parseInt(hex1.substring(i, i + 2), 16);
int val2 = Integer.parseInt(hex2.substring(i, i + 2), 16);
int xorValue = val1 ^ val2;
result.append(String.format("%02X", xorValue));
}
return result.toString();
}
private static String RK(String key, int round) {
int partLength = key.length() / 4;
String[] w = new String[8];
for (int i = 0; i < 4; i++) {
w[i] = key.substring(i * partLength, (i + 1) * partLength);
}
String g = w[3].substring(2) + w[3].substring(0, 2);
StringBuilder substituted = new StringBuilder();
for (int i = 0; i < g.length(); i += 2) {
int row = Character.digit(g.charAt(i), 16);
int col = Character.digit(g.charAt(i + 1), 16);
substituted.append(String.format("%02X", S_BOX[row][col]));
}
g = substituted.toString();
int[] Rcon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};
int gInt = Integer.parseUnsignedInt(g.substring(0, 2), 16) ^ Rcon[round - 1];
g = String.format("%02X", gInt) + g.substring(2);
w[4] = xorHexStrings(w[0], g);
w[5] = xorHexStrings(w[4], w[1]);
w[6] = xorHexStrings(w[5], w[2]);
w[7] = xorHexStrings(w[6], w[3]);
return w[4] + w[5] + w[6] + w[7];
}
private static String subBytes(String matrix) {
StringBuilder substituted = new StringBuilder();
for (int i = 0; i < matrix.length(); i += 2) {
int row = Character.digit(matrix.charAt(i), 16);
int col = Character.digit(matrix.charAt(i + 1), 16);
substituted.append(String.format("%02X", S_BOX[row][col]));
}
return substituted.toString();
}
private static String shiftRows(String matrix) {
String[] bytes = new String[16];
for (int i = 0; i < 16; i++) {
bytes[i] = matrix.substring(i * 2, (i + 1) * 2);
}
int[] shiftOrder = {0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11};
StringBuilder result = new StringBuilder();
for (int i = 0; i < 16; i++) {
result.append(bytes[shiftOrder[i]]);
}
return result.toString();
}
private static String mixColumns(String matrix) {
int[][] state = new int[4][4];
for (int i = 0; i < 16; i++) {
int col = i / 4;
int row = i % 4;
state[row][col] = Integer.parseInt(matrix.substring(i * 2, (i + 1) * 2), 16);
}
int[][] newState = mixColumnsMatrix(state);
StringBuilder result = new StringBuilder();
for (int col = 0; col < 4; col++) {
for (int row = 0; row < 4; row++) {
result.append(String.format("%02X", newState[row][col]));
}
}
return result.toString();
}
private static int[][] mixColumnsMatrix(int[][] state) {
int[][] fixedMatrix = {
{0x02, 0x03, 0x01, 0x01},
{0x01, 0x02, 0x03, 0x01},
{0x01, 0x01, 0x02, 0x03},
{0x03, 0x01, 0x01, 0x02}
};
int[][] newState = new int[4][4];
for (int col = 0; col < 4; col++) {
for (int row = 0; row < 4; row++) {
int val = 0;
for (int i = 0; i < 4; i++) {
val ^= gfMultiply(fixedMatrix[row][i], state[i][col]);
}
newState[row][col] = val;
}
}
return newState;
}
private static int gfMultiply(int a, int b) {
int p = 0;
for (int i = 0; i < 8; i++) {
if ((b & 1) != 0) {
p ^= a;
}
boolean bit = (a & 0x80) != 0;
a <<= 1;
if (bit) {
a ^= 0x1B;
}
b >>= 1;
}
return p & 0xFF;
}
private static String addRoundKey(String state, String roundKey) {
return xorHexStrings(state, roundKey);
}
private static String encryptRound(String state, String roundKey, boolean finR) {
state = subBytes(state);
state = shiftRows(state);
if (!finR) {
state = mixColumns(state);
}
state = addRoundKey(state, roundKey);
return state;
}
public static String encrypt(String data, String key) {
String dataHex = toHex(data);
String keyHex = toHex(key);
int keyLength = key.length();
int noR;
if (keyLength == 16) noR = 10;
else if (keyLength == 24) noR = 12;
else noR = 14;
String[] roundKeys = new String[noR + 1];
roundKeys[0] = keyHex;
System.out.println("Round Key 0 : "+roundKeys[0]);
for (int i = 1; i <= noR; i++) {
roundKeys[i] = RK(roundKeys[i-1], i);
System.out.println("Round Key "+i+" : "+roundKeys[i]);
}
System.out.println();
String state = addRoundKey(dataHex, roundKeys[0]);
for (int round = 1; round < noR; round++) {
state = encryptRound(state, roundKeys[round], false);
System.out.println("Matrix Round "+round+" : "+state);
}
state = encryptRound(state, roundKeys[noR], true);
System.out.println("Matrix Round "+noR+" : "+state);
System.out.println();
return state;
}
public static void main(String[] args) {
Scanner sc = new Scanner(System.in);
System.out.print("Enter 128-bit data (16 characters): ");
String data = sc.nextLine();
if (data.length() != 16) {
System.out.println("Error: Data must be exactly 16 ASCII characters.");
sc.close();
return;
}
System.out.print("Enter key (16, 24, or 32 characters): ");
String key = sc.nextLine();
int keyLength = key.length();
if (keyLength != 16 && keyLength != 24 && keyLength != 32) {
System.out.println("Error: Key must be exactly 16, 24, or 32 ASCII characters.");
sc.close();
return;
}
String encryptedHex = encrypt(data, key);
System.out.println("\nEncrypted (hex): " + encryptedHex);
sc.close();
}
}
