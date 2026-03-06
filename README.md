# Hybrid Encryption

Implementation of a hybrid encryption system combining the **Hill cipher** and **Playfair cipher**.

---

## Overview

This program implements a two-stage encryption pipeline called **hillplayfair** that encrypts plaintext using two classical cryptographic techniques.

---

## Stage 1 — Hill Cipher

The plaintext is first encrypted using the **Hill cipher**.

Features:

- Uses an **n × n integer key matrix**
- Block size **n**, where **2 ≤ n ≤ 9**
- Arithmetic performed **modulo 26**
- Alphabet mapping:

```
A = 0 ... Z = 25
```

The plaintext is divided into blocks of size **n**, and each block is multiplied by the key matrix to produce the Hill-encrypted text.

---

## Stage 2 — Playfair Cipher

The output of the Hill cipher is then encrypted using a **Playfair digraph cipher**.

Features:

- Uses a **Playfair keyword** from a keyword file
- Letters **I and J are combined**
- Encryption operates on **pairs of characters (digraphs)**

---

## Encryption Pipeline

```
Plaintext
   ↓
Hill Cipher
   ↓
Playfair Cipher
   ↓
Final Ciphertext
```

---

## Language

C

---

## Compilation

Compile the program using GCC:

```bash
gcc -O2 -std=c11 -o hillplayfair hillplayfair.c
```

---

## Running the Program

Run encryption with:

```bash
./hillplayfair encrypt key.txt plain.txt keyword.txt
```

### Arguments

```
encrypt       → encryption mode
key.txt       → Hill cipher key matrix
plain.txt     → plaintext input
keyword.txt   → Playfair keyword
```

---

## Example Input Files

### Hill Cipher Key File (`key.txt`)

```
2
2 4
3 5
```

Explanation:

```
2 → matrix dimension

Key matrix:
2 4
3 5
```

---

### Plaintext File (`plain.txt`)

```
Not only is the Universe stranger than we think
```

---

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
Not only is the Universe stranger than we think

Preprocessed Plaintext:
NOTONLYISTHEUNIVERSESTRANGERTHANWETHINK

Hill Cipher Key Dimension:
2

Hill Cipher Key Matrix:
2 4
3 5

Padded Hill Cipher Plaintext:
NOTONLYISTHEUNIVERSESTRANGERTHANWETHINKX

Ciphertext after Hill Cipher:
...

Playfair Keyword:
MONARCHY

Playfair Table:
M O N A R
C H Y B D
E F G I K
L P Q S T
U V W X Z

Ciphertext after Playfair:
...
```

---

## Program Features

- Plaintext preprocessing
- Hill cipher block encryption
- Playfair digraph encryption
- Automatic padding for Hill cipher blocks
- Playfair table generation from keyword

---

## Encryption Rules Summary

### Hill Cipher

- Works on **vectors of size n**
- Matrix multiplication **mod 26**

### Playfair Cipher Rules

1. **Same row**  
   Replace each letter with the letter to the **right**.

2. **Same column**  
   Replace each letter with the letter **below**.

3. **Rectangle rule**  
   Swap the columns of the letters.

---

## Example Playfair Table (Keyword: MONARCHY)

```
M O N A R
C H Y B D
E F G I K
L P Q S T
U V W X Z
```

---
