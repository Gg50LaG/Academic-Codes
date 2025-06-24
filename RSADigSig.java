import java.util.Scanner;
import java.util.Random;
public class RSADigitalSignature {
public static int modExp(int base, int exp, int mod) {
int result = 1;
base = base % mod;
while (exp > 0) {
if (exp % 2 == 1) {
result = (result * base) % mod;
}
base = (base * base) % mod;
exp /= 2;
}
return result;
}
public static int gcd(int a, int b) {
if (b == 0)
return a;
return gcd(b, a % b);
}
public static int modInverse(int e, int phi) {
for (int d = 1; d < phi; d++) {
if ((e * d) % phi == 1) {
return d;
}
}
return -1;
}
public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);
System.out.print("Enter prime number (p): ");
int p = scanner.nextInt();
System.out.print("Enter prime number (q): ");
int q = scanner.nextInt();
int n = p * q;
int phi = (p - 1) * (q - 1);
System.out.println("phi: "+phi);
int e = 3;
while (gcd(e, phi) != 1) {
e++;
}
int d = modInverse(e, phi);
System.out.println("Public key (e, n): (" + e + ", " + n + ")");
System.out.println("Private key (d, n): (" + d + ", " + n + ")");
System.out.print("Enter message hash (H): ");
int H = scanner.nextInt();
int signature = modExp(H, d, n);
System.out.println("Digital Signature: " + signature);
int verification = modExp(signature, e, n);
System.out.println("Verification: " + (verification == H ? "Valid Signature" : "Invalid Signature"));
scanner.close();
}
}
