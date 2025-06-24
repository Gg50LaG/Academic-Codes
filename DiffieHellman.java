import java.util.Scanner;
public class DiffieHellman {
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
public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);
System.out.print("Enter prime number (p): ");
int p = scanner.nextInt();
System.out.print("Enter primitive root (g): ");
int g = scanner.nextInt();
System.out.print("Enter private key of A: ");
int a = scanner.nextInt();
System.out.print("Enter private key of B: ");
int b = scanner.nextInt();
int A_public = modExp(g, a, p);
int B_public = modExp(g, b, p);
System.out.println("Public key of A: " + A_public);
System.out.println("Public key of B: " + B_public);
int sharedKeyA = modExp(B_public, a, p);
int sharedKeyB = modExp(A_public, b, p);
System.out.println("Shared Key computed by A: " + sharedKeyA);
System.out.println("Shared Key computed by B: " + sharedKeyB);
System.out.print("Enter private key of Attacker(MITM): ");
int attackerPrivate = scanner.nextInt();
int attackerPublicA = modExp(g, attackerPrivate, p);
int attackerPublicB = modExp(g, attackerPrivate, p);
int interceptedKeyA = modExp(attackerPublicA, a, p);
int interceptedKeyB = modExp(attackerPublicB, b, p);
System.out.println("MITM Attack: Attacker computes key with A: " + interceptedKeyA);
System.out.println("MITM Attack: Attacker computes key with B: " + interceptedKeyB);
scanner.close();
}
}
