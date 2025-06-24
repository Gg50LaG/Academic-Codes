import java.util.Scanner;
public class ElGamalDigitalSignature {
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
System.out.print("Enter message hash (H): ");
int H = scanner.nextInt();
System.out.print("Enter random number (k): ");
int k = scanner.nextInt();
int y = modExp(g, x, p);
System.out.println("Public key (p, g, y): (" + p + ", " + g + ", " + y + ")");
int r = modExp(g, k, p);
int kInverse = modInverse(k, p - 1);
int s = (kInverse * (H - x * r)) % (p - 1);
if (s < 0) s += (p - 1);
System.out.println("Signature (r, s): (" + r + ", " + s + ")");
int v1 = modExp(g, H, p);
int v2 = (modExp(y, r, p) * modExp(r, s, p)) % p;
System.out.println("Verification: " + (v1 == v2 ? "Valid Signature" : "Invalid Signature"));
scanner.close();
}
}
