import java.util.Scanner;
public class ElGamal {
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
public static int modInverse(int a, int mod) {
int m0 = mod, t, q;
int x0 = 0, x1 = 1;
if (mod == 1) return 0;
while (a > 1) {
q = a / mod;
t = mod;
mod = a % mod;
a = t;
t = x0;
x0 = x1 - q * x0;
x1 = t;
}
if (x1 < 0) x1 += m0;
return x1;
}
public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);
System.out.print("Enter prime number (p): ");
int p = scanner.nextInt();
System.out.print("Enter primitive root (g): ");
int g = scanner.nextInt();
System.out.print("Enter private key (x): ");
int x = scanner.nextInt();
System.out.print("Enter message (M): ");
int M = scanner.nextInt();
System.out.print("Enter random number (k): ");
int k = scanner.nextInt();
int y = modExp(g, x, p);
System.out.println("Public key (p, g, y): (" + p + ", " + g + ", " + y + ")");
int c1 = modExp(g, k, p);
int c2 = (M * modExp(y, k, p)) % p;
System.out.println("Ciphertext (c1, c2): (" + c1 + ", " + c2 + ")");
int kInverse = modExp(c1, x, p);
int decryptedM = (c2 * modInverse(kInverse, p)) % p;
System.out.println("Decrypted message: " + decryptedM);
scanner.close();
}
}
