# Hybrid Encryption

Implementation of a hybrid encryption system combining the **Hill cipher** and **Playfair cipher**.

## Overview

This program implements a two-stage encryption pipeline called **hillplayfair** that encrypts plaintext using two classical cryptographic techniques.

### Stage 1 — Hill Cipher
The plaintext is first encrypted using the Hill cipher.

- Uses an **n × n integer key matrix**
- Block size **n**, where **2 ≤ n ≤ 9**
- Arithmetic performed **modulo 26**
- Alphabet mapping: **A = 0 ... Z = 25**

The plaintext is divided into blocks of size *n*, and each block is multiplied by the key matrix to produce the Hill-encrypted text.

### Stage 2 — Playfair Cipher
The output of the Hill cipher is then encrypted using a **Playfair digraph cipher**.

- Uses a **Playfair keyword** from a keyword file
- Letters **I and J are combined**
- Encryption operates on **pairs of characters (digraphs)**

### Encryption Pipeline

```
Plaintext
   ↓
Hill Cipher
   ↓
Playfair Cipher
   ↓
Final Ciphertext
```

## Language

C

## Usage

Compile the program:

```
gcc -O2 -std=c11 -o hillplayfair hillplayfair.c```

## Run the encryption:

```
./hillplayfair encrypt key.txt plain.txt keyword.txt```

## Example Input Files

### Hill Cipher Key File (`key.txt`)

```
2
2 4
3 5
```

### Plaintext File (`plain.txt`)

```
Not only is the Universe stranger than we think
```

### Playfair Keyword File (`keyword.txt`)

```
MONARCHY
```

---

## Example Program Execution

```
$ ./hillplayfair encrypt key.txt plain.txt keyword.txt

Mode:
Encryption Mode

Original Plaintext:
abcdefghijklmnopqrstuvwxyz0123456789
0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ

Preprocessed Plaintext:
ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ

Hill Cipher Key Dimension:
2

Hill Cipher Key Matrix:
1 0
0 1

Padded Hill Cipher Plaintext:
ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ

Ciphertext after Hill Cipher:
ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ

Playfair Keyword:
MONARCHY

Playfair Table:
M O N A R
C H Y B D
E F G I K
L P Q S T
U V W X Z

Ciphertext after Playfair:
BIHCFGFYSAKEUCANQSATLZWXWBXRDHCKGIBFKEUCANQSATLZWXWBUZ
```
