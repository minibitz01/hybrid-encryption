
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *OriginalPlainText;
char *PreProcessedPlainText;
char *PaddedPlainText;
int matrixLength = 0;
int **ArrTwodee; //n*n matrix 
char *Ciphertext; 
char PlayfairKeyword[256]; 
char ManipulatedKeyword[256]; 
char *PreparedFair;
char alphabet_list[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
char *PlayfairCypherText; 

void readinPlainText(FILE *PainText); 
void ProcessingPlainText(); 
void readinHillCipher(FILE *CipherKey);
void allocateRows(int row, int cols); 
void Padding(); 
void HillCipher(); 
void readinPlayFair(FILE *KeyWord); 
void KeywordManip(); 
void PlayfairTable(char matrix[5][5]);
void PrepareString(); 
void encrypt_playfair_cipher(char matrix[5][5]);
void search_element(char matrix[5][5], char element, int *row, int *col); 
void Freedom(); 

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        printf("Usage: ./hillplayfair encrypt key plain keyword\n"); 
        return 1; 
    }
    printf("Mode: \n");
    printf("Encryption Mode \n");
    printf("\n"); 

    //fist read in plain text 
    FILE *PainText =  fopen(argv[3], "r");
    FILE *CipherKey =  fopen(argv[2], "r");
    FILE *KeyWord =  fopen(argv[4], "r");

    readinPlainText(PainText);
    ProcessingPlainText(); 
    readinHillCipher(CipherKey);
    Padding();

    HillCipher(); 

    readinPlayFair(KeyWord);
    KeywordManip(); 
    char matrix[5][5]; 
    PlayfairTable(matrix); 
    PrepareString(); 
    encrypt_playfair_cipher(matrix); 

    Freedom(); 

    return 0;
}

void readinPlainText(FILE *PainText)
{
    if(PainText == NULL)
    {
        printf("Unable to open file\n");
        exit(1); 
    }

    char buffer[256];
    size_t total_length = 0; 

    OriginalPlainText = malloc(1); 
    if(OriginalPlainText == NULL)
    {
        printf("Unable to allocate memory\n");
        exit(1); 
    }
    OriginalPlainText[0] = '\0'; 

    //read in buffer 
    while(fgets(buffer, sizeof(buffer), PainText) != NULL)
    {
        size_t buffer_length = strlen(buffer);
        size_t new_length = total_length + buffer_length + 1; 

        // Reallocate memory for PlainText
        char *TTemp = realloc(OriginalPlainText, new_length);

        if(TTemp == NULL)
        {
            printf("Cannot read in Original Plaintext\n");
            exit(1);
        }
        OriginalPlainText = TTemp; 
        strcpy(OriginalPlainText + total_length, buffer);
        total_length += buffer_length;
    }  

    printf("Original Plaintext: \n"); 
    printf("%s", OriginalPlainText);
    printf("\n"); 
}

void ProcessingPlainText()
{
    //preprocessing 
    int counter = 0;
    int length = strlen(OriginalPlainText);
    char temp[length + matrixLength + 1]; 

    for(int i = 0; OriginalPlainText[i] != '\0'; i++)
    {
        char c = OriginalPlainText[i]; 

        if(isalpha(c))
        { 
            temp[counter] = toupper(c); 
            counter++; 
        } 
        else continue; 
    } 
    temp[counter] = '\0';
    int TempLen = counter; 

    PreProcessedPlainText = malloc(TempLen + 1); 
    if(PreProcessedPlainText == NULL)
    {
        printf("Memory Error in reallcing Plaintext (Preprocessing)"); 
        exit(1); 
    }
    strcpy(PreProcessedPlainText, temp); 
    printf("Preprocessed Plaintext: \n");

    int i = 0; 
    int charactersPrinted = 0; 
    while(PreProcessedPlainText[i] != '\0')
    {
        if(charactersPrinted == 80)
        {
            printf("\n"); 
            charactersPrinted = 0; 
        }
        printf("%c", PreProcessedPlainText[i]); 
        i++;
        charactersPrinted++;  
    }
    printf("\n");  
    printf("\n"); 
}

void readinHillCipher(FILE *CipherKey)
{
    if(CipherKey == NULL)
    {
        printf("Unable to open file\n");
        exit(1); 
    }

    //read in matrix size 
    if(fscanf(CipherKey, "%d", &matrixLength) != 1)
    {
        printf("Cannot read in matrix size\n");
        exit(1);
    }
    printf("Hill Cipher Key Dimension: \n"); 
    printf("%d\n", matrixLength);
    printf("\n");

    //allocate space for the double array and read in values 
    ArrTwodee = malloc(matrixLength * sizeof(int*));
    int rows = matrixLength;
    int col = matrixLength; 

    allocateRows(rows-1, col);

    printf("Hill Cipher Key Matrix: \n"); 
    for(int i = 0; i < matrixLength; i++)
    {
        for(int j = 0; j < matrixLength; j++)
        {
            if(fscanf(CipherKey, "%d", &ArrTwodee[i][j])!=1)
            {
                printf("Cannot read in matrix size\n");
                exit(1); 
            }
            printf("%4d ", ArrTwodee[i][j]); 
        } 
        printf("\n"); 
    }
}

void allocateRows(int row, int cols)
{
    if (row < 0) return;
    ArrTwodee[row] = (int*)malloc(cols * sizeof(int)); 

    allocateRows(row - 1, cols);
}

void Padding()
{
    //padding 
    int counter = strlen(PreProcessedPlainText);
    char temp[counter+matrixLength+1]; 
    strcpy(temp, PreProcessedPlainText);  

    if(counter % matrixLength != 0)
    {
        while(counter % matrixLength != 0)
        {
            temp[counter] = 'X'; 
            counter++; 
        }
    }
    temp[counter] = '\0';
    printf("\n"); 

    PaddedPlainText = malloc(counter+1); 
    if(PaddedPlainText == NULL)
    {
        printf("Memory Error in reallcing Plaintext (Padding)"); 
        exit(1); 
    }

    printf("Padded Hill Cipher Plaintext: \n");
    strcpy(PaddedPlainText, temp);

    int i = 0; 
    int charactersPrinted = 0; 
    while(PaddedPlainText[i] != '\0')
    {
        if(charactersPrinted == 80)
        {
            printf("\n"); 
            charactersPrinted = 0; 
        }
        printf("%c", PaddedPlainText[i]); 
        i++;
        charactersPrinted++;  
    }
      
    printf("\n");
    printf("\n");
}

void HillCipher()
{

    int length = strlen(PaddedPlainText); 
    int *Vector = malloc(matrixLength * sizeof(int));

    // //new ciphertext  
    Ciphertext = malloc((length+1) * sizeof(char)); 
    
    for(int i = 0; i < length; i+=matrixLength)
    {
        for(int j = 0; j < matrixLength; j++)
        {
            Vector[j] = PaddedPlainText[i+j]-'A';
        } 
        //multiplication (LA)
        for(int k = 0; k < matrixLength; k++)
        {
            int sum = 0; 
            //cols
            for(int l = 0; l < matrixLength; l++)
            {
                sum += ArrTwodee[k][l] * Vector[l]; 
            }  
            Ciphertext[i+k] = (sum%26) + 'A';
        } 
    } 
    
    
    Ciphertext[length] = '\0'; 
    printf("Ciphertext after Hill Cipher: \n");

    int i = 0; 
    int charactersPrinted = 0; 
    while(Ciphertext[i] != '\0')
    {
        if(charactersPrinted == 80)
        {
            printf("\n"); 
            charactersPrinted = 0; 
        }
        printf("%c", Ciphertext[i]); 
        i++;
        charactersPrinted++;  
    }
    printf("\n");
    printf("\n");
    free(Vector);
}

void readinPlayFair(FILE *KeyWord)
{
    if(KeyWord == NULL)
    {
        printf("Unable to open file\n");
        exit(1); 
    }

    char buffer[256];

    //read in matrix size 
    if(fscanf(KeyWord, "%255s", buffer) != 1)
    {
        printf("Cannot read in Original Plaintext\n");
        exit(1);
    }
    strcpy(PlayfairKeyword, buffer); 
}

void KeywordManip()
{
     int len = strlen(PlayfairKeyword); 

    strcpy(ManipulatedKeyword, PlayfairKeyword);
    
    for(int i = 0; ManipulatedKeyword[i] != '\0'; i++)
    {
        ManipulatedKeyword[i] = toupper(ManipulatedKeyword[i]); 
        if(ManipulatedKeyword[i] == 'J') ManipulatedKeyword[i] = 'I';
    }

    for(int i = 0; ManipulatedKeyword[i] != '\0'; i++)
    {
        for(int j = i + 1; j < len; )
        {
            if(ManipulatedKeyword[i] == ManipulatedKeyword[j])
            {
                for(int k = j; k < len; k++)
                {
                    ManipulatedKeyword[k] = ManipulatedKeyword[k+1]; 
                } 
                len--; 
            }
            else {j++;}
        }
    }
    ManipulatedKeyword[len] = '\0'; 
    printf("Playfair Keyword: \n"); 
    printf("%s\n", ManipulatedKeyword);
    printf("\n"); 
} 

void PlayfairTable(char matrix[5][5]) 
{
   char used[26] = {0};
   int i, index = 0;

   for (i = 0; ManipulatedKeyword[i] != '\0'; i++) 
   {
    char c = ManipulatedKeyword[i]; 
    if(c == 'J') c = 'I'; 
    if(!used[c - 'A']) 
    {
        used[c - 'A'] = 1;
        matrix[index / 5][index % 5] = c;
        index++;
    }
   }

   for(i = 0; alphabet_list[i] != '\0'; i++) 
   {
      if(!used[alphabet_list[i] - 'A']) 
      {
        used[alphabet_list[i] - 'A'] = 1;
        matrix[index / 5][index % 5] = alphabet_list[i];
        index++;
      }
   }

   printf("Playfair Table: \n"); 
   for (i = 0; i<5; i++) 
   {
    for(int j = 0; j < 5; j++)
    {
        printf("%c ", matrix[i][j]); 
    }
    printf("\n"); 
   }
   printf("\n");
}

void PrepareString()
{
    int len = strlen(Ciphertext);
    PreparedFair = malloc((len*2+2));
    char *temp = malloc((len*2+2));

    strcpy(temp, Ciphertext); 

    for(int i = 0; temp[i] != '\0'; i+=2)
    {
        // Replace J with I.
        for(int j = 0; j < 2; j++)
        {
            if(temp[i+j] == 'J') temp[i+j] = 'I';
        } 

        if(temp[i] == temp[i+1])
        {
            //move forward 
            for(int k = len; k >= i+1; k--)
            {
                temp[k+1] = temp[k]; 
            }
            if(temp[i] == 'X') temp[i+1] = 'Z'; 
            else temp[i+1] = 'X'; 
            len++; 
        }
    }
     
    if(len % 2 == 1)
    { 
        char c = temp[len-1]; 
        char x = 'Z';
        
        if(c == 'Z') temp[len] = 'X';
        else
        {
            temp[len] = x; 
        }
        len++; 
    }
    temp[len] = '\0'; 
    strcpy(PreparedFair, temp);
    free(temp);  
}

void encrypt_playfair_cipher(char matrix[5][5]) 
{
   int len = strlen(PreparedFair);
   PlayfairCypherText = malloc(len+1);

   strcpy(PlayfairCypherText, PreparedFair); 

   int i, row1, col1, row2, col2;

   for (i = 0; i < len; i += 2) 
   {
    if(PlayfairCypherText[i] == 'J') PlayfairCypherText[i] = 'I'; 
    search_element(matrix, PreparedFair[i], &row1, &col1);
    if(PlayfairCypherText[i+1] == 'J') PlayfairCypherText[i+1] = 'I'; 
    search_element(matrix, PreparedFair[i + 1], &row2, &col2);

    if(row1 == row2)
    {
        PlayfairCypherText[i] = matrix[row1][(col1 + 1) % 5];
        PlayfairCypherText[i + 1] = matrix[row2][(col2 + 1) % 5];
    }
    else if (col1 == col2) 
    {
        PlayfairCypherText[i] = matrix[(row1 + 1) % 5][col1];
        PlayfairCypherText[i + 1] = matrix[(row2 + 1) % 5][col2];
    }
    else 
    {
        PlayfairCypherText[i] = matrix[row1][col2];
        PlayfairCypherText[i + 1] = matrix[row2][col1];
        }
    }
   PlayfairCypherText[len] = '\0';
   printf("Ciphertext after Playfair: \n");

   i = 0; 
   int charactersPrinted = 0; 

   while(PlayfairCypherText[i] != '\0')
   {
    if(charactersPrinted == 80)
    {
        printf("\n"); 
        charactersPrinted = 0; 
    }
        printf("%c", PlayfairCypherText[i]); 
        i++;
        charactersPrinted++;  
    }
    printf("\n");
}

void search_element(char matrix[5][5], char element, int *row, int *col) 
{
   for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
         if (matrix[i][j] == element) {
            *row = i;
            *col = j;
            return;
         }
      }
   }
}

void Freedom()
{
    free(OriginalPlainText);
    free(PreProcessedPlainText);
    free(PaddedPlainText);
    for(int i = 0; i < matrixLength; i++)
    {
        free(ArrTwodee[i]);
    }
    free(ArrTwodee); 
    free(Ciphertext);
    free(PreparedFair); 
    free(PlayfairCypherText); 
}
