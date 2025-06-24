import java.util.*;
public class PlayfairCipher {
private char[][] matrix;
private static final int SIZE = 5;
public PlayfairCipher(String key) {
matrix = createMatrix(key);
}
private char[][] createMatrix(String key) {
char[][] matrix = new char[SIZE][SIZE];
StringBuilder keyBuilder = new StringBuilder();
boolean[] used = new boolean[26];
key = key.toUpperCase().replaceAll("[^A-Z]", "").replace("J", "I");
for (char c : key.toCharArray()) {
if (!used[c - 'A']) {
keyBuilder.append(c);
used[c - 'A'] = true;
}
}
for (char c = 'A'; c <= 'Z'; c++) {
if (c != 'J' && !used[c - 'A']) {
keyBuilder.append(c);
}
}
int index = 0;
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
matrix[i][j] = keyBuilder.charAt(index++);
}
}
return matrix;
}
private String preprocess(String input) {
input = input.toUpperCase().replaceAll("[^A-Z]", "").replace("J", "I");
StringBuilder result = new StringBuilder();
for (int i = 0; i < input.length(); i++) {
if (i > 0 && input.charAt(i) == input.charAt(i - 1)) {
result.append('X');
}
result.append(input.charAt(i));
}
if (result.length() % 2 != 0) {
result.append('X');
}
return result.toString();
}
private int[] findPosition(char c) {
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
if (matrix[i][j] == c) {
return new int[]{i, j};
}
}
}
return null;
}
public String encrypt(String pt) {
pt = preprocess(pt);
StringBuilder ciphertext = new StringBuilder();
for (int i = 0; i < pt.length(); i += 2) {
char a = pt.charAt(i);
char b = pt.charAt(i + 1);
int[] posA = findPosition(a);
int[] posB = findPosition(b);
if (posA[0] == posB[0]) {
ciphertext.append(matrix[posA[0]][(posA[1] + 1) % SIZE]);
ciphertext.append(matrix[posB[0]][(posB[1] + 1) % SIZE]);
} else if (posA[1] == posB[1]) {
ciphertext.append(matrix[(posA[0] + 1) % SIZE][posA[1]]);
ciphertext.append(matrix[(posB[0] + 1) % SIZE][posB[1]]);
} else {
ciphertext.append(matrix[posA[0]][posB[1]]);
ciphertext.append(matrix[posB[0]][posA[1]]);
}
}
return ciphertext.toString();
}
public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);
System.out.println("Enter the key:");
String key = scanner.nextLine();
PlayfairCipher cipher = new PlayfairCipher(key);
System.out.println("Enter the plaintext:");
String pt = scanner.nextLine();
String encrypted = cipher.encrypt(pt);
System.out.println("Encrypted text: " + encrypted);
scanner.close();
}
}
