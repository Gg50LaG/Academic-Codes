import java.math.BigInteger;
import java.util.*;
public class RSA {
public static int[] textToNumbers(String text) {
text = text.toUpperCase();
int[] numbers = new int[text.length()];
for (int i = 0; i < text.length(); i++) {
if (text.charAt(i) >= 'A' && text.charAt(i) <= 'Z') {
numbers[i] = text.charAt(i) - 'A';
}
}
return numbers;
}
public static String numbersToText(int[] numbers) {
StringBuilder sb = new StringBuilder();
for (int num : numbers) {
sb.append((char) (num + 'A'));
}
return sb.toString();
}
public static int gcd(int a, int b) {
while (b != 0) {
int temp = b;
b = a % b;
a = temp;
}
return a;
}
public static int modInverse(int e, int phi) {
for (int d = 2; d < phi; d++) {
if ((d * e) % phi == 1) {
return d;
}
}
return -1;
}
public static BigInteger[] encrypt(int[] plaintext, int e, int n) {
BigInteger[] ciphertext = new BigInteger[plaintext.length];
for (int i = 0; i < plaintext.length; i++) {
ciphertext[i] = BigInteger.valueOf(plaintext[i]).pow(e).mod(BigInteger.valueOf(n));
}
return ciphertext;
}
public static int[] decrypt(BigInteger[] ciphertext, int d, int n) {
int[] decryptedNumbers = new int[ciphertext.length];
for (int i = 0; i < ciphertext.length; i++) {
decryptedNumbers[i] = ciphertext[i].pow(d).mod(BigInteger.valueOf(n)).intValue();
}
return decryptedNumbers;
}
public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);
System.out.print("Enter prime number p: ");
int p = scanner.nextInt();
System.out.print("Enter prime number q: ");
int q = scanner.nextInt();
int n = p * q;
int phi = (p - 1) * (q - 1);
int e = 2;
while (e < phi && gcd(e, phi) != 1) {
e++;
}
int d = modInverse(e, phi);
if (d == -1) {
System.out.println("Could not find modular inverse. Choose different p and q.");
scanner.close();
return;
}
System.out.println("Public key (e, n): (" + e + ", " + n + ")");
System.out.println("Private key (d, n): (" + d + ", " + n + ")");
System.out.print("Enter message (word or number): ");
if (scanner.hasNextInt()) {
int number = scanner.nextInt();
BigInteger[] encryptedNumber = encrypt(new int[]{number}, e, n);
System.out.println("Encrypted number: " + encryptedNumber[0]);
int[] decryptedNumber = decrypt(encryptedNumber, d, n);
System.out.println("Decrypted number: " + decryptedNumber[0]);
} else {
String message = scanner.next();
int[] plaintextNumbers = textToNumbers(message);
BigInteger[] encryptedText = encrypt(plaintextNumbers, e, n);
System.out.print("Encrypted message: ");
for (BigInteger num : encryptedText) {
System.out.print(num + " ");
}
System.out.println();
int[] decryptedNumbers = decrypt(encryptedText, d, n);
String decryptedText = numbersToText(decryptedNumbers);
System.out.println("Decrypted message: " + decryptedText);
}
scanner.close();
}
}
