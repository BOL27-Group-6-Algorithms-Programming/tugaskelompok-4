#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
  char code[10];
  char name[255];
  char genre[255];
  double price;
  int stock;
};

struct purchaseHistory
{
  char code[10];
  char name[255];
  char genre[20];
  double price;
  int qty;
  int orderID;
};

// Function to read the data inside databuku.txt
int readBooks(struct Book books[], int maxBooks)
{
  FILE *file = fopen("databuku.txt", "r");
  if (file == NULL)
  {
    return 0;
  }

  int count = 0;
  char line[256];

  while (fgets(line, sizeof(line), file) && count < maxBooks)
  {
    if (sscanf(line, "Kode: %s", books[count].code) != 1)
    {
      continue;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Name: %[^\n]", books[count].name) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Genre: %[^\n]", books[count].genre) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Price: %lf", &books[count].price) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Stock: %d", &books[count].stock) != 1)
    {
      break;
    }
    count++;
  }

  fclose(file);
  return count;
}

// Function to write into databuku.txt
void writeBooks(struct Book books[], int count)
{
  FILE *file = fopen("databuku.txt", "w");
  if (file == NULL)
  {
    printf("Failed to write data to file.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "Kode: %s\nName: %s\nGenre: %s\nPrice: %.2lf\nStock: %d\n#\n",
            books[i].code, books[i].name, books[i].genre, books[i].price, books[i].stock);
  }

  fclose(file);
}

// Function to write into datapembelian.txt
void writePurchaseHistory(struct purchaseHistory history[], int count)
{
  FILE *file = fopen("datapembelian.txt", "w");
  if (file == NULL)
  {
    printf("Failed to write data to file.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "Kode: %s\nName: %s\nGenre: %s\nPrice: %.2lf\nQuantity: %d\nOrderID: %d\n#\n",
            history[i].code, history[i].name, history[i].genre, history[i].price, history[i].qty, history[i].orderID);
  }

  fclose(file);
}

// Function to display the data from databuku.txt
void displayBooks(struct Book books[], int count)
{
  printf("\nBook's List:\n");
  for (int i = 0; i < count; i++)
  {
    printf("%d.| Code: %s, Name: %s, Genre: %s, Price: Rp.%.2lf, Stock: %d |\n", i + 1, books[i].code, books[i].name, books[i].genre, books[i].price, books[i].stock);
  }
}

// Function to add a new record to the databuku.txt
void addBook(struct Book books[], int *count)
{
  char newCode[10];
  int isCodeValid = 1;

  printf("\nEnter book details:\n");
  do
  {
    printf("Kode: ");
    if (scanf("%9s", newCode) != 1)
    {
      printf("Invalid input. Please enter a valid integer.\n");
      // Clear the input buffer
      while (getchar() != '\n')
        ;
    }
    else
    {
      int code;
      if (sscanf(newCode, "%d", &code) == 1 && code > 0)
      {
        isCodeValid = 1;
      }
      else
      {
        printf("Invalid input. Please enter a valid positive integer.\n");
        isCodeValid = 0;
      }
    }
  } while (!isCodeValid);

  int editExistingBook = 0;

  // If the book with the same code already exists
  for (int i = 0; i < *count; i++)
  {
    if (strcmp(newCode, books[i].code) == 0)
    {
      int additionalStock;
      int option;

      printf("Book with the same code already exists. Do you want to edit this book stock? (0 = No | 1 = Yes) ");
      scanf(" %d", &option);

      if (option == 0)
      {
        return; // Exit the function without making any changes
      }
      else if (option == 1)
      {
        editExistingBook = 1;
        printf("Enter additional stock (the value you input will be added with the initial stock value): ");
        scanf("%d", &additionalStock);

        if (additionalStock > 0)
        {
          books[i].stock += additionalStock;
          printf("Stock updated successfully. Total stock: %d\n", books[i].stock);
        }
        else
        {
          printf("Invalid stock quantity. No changes were made.\n");
        }
      }
      else
      {
        printf("Invalid option. No changes were made.\n");
      }
    }
  }

  // If the book with the same code does not exist, proceed to add it
  if (!editExistingBook)
  {
    strcpy(books[*count].code, newCode);

    int inputValidation = 1;
    printf("Name: ");
    scanf(" %254[^\n]", books[*count].name);
    printf("Genre (To add more than 1 genre, use this format (Genre1,Genre2)): ");
    scanf(" %254[^\n]", books[*count].genre);
    printf("Price: ");
    scanf("%lf", &books[*count].price);
    printf("Stock: ");
    scanf("%d", &books[*count].stock);

    (*count)++;
    printf("Book added successfully.\n");
  }
}

// Function to read purchase history from datapembelian.txt
int readPurchaseHistory(struct purchaseHistory history[], int maxHistory)
{
  FILE *file = fopen("datapembelian.txt", "r");
  if (file == NULL)
  {
    return 0;
  }

  int count = 0;
  char line[256];

  while (fgets(line, sizeof(line), file) && count < maxHistory)
  {
    if (sscanf(line, "Kode: %s", history[count].code) != 1)
    {
      continue;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Name: %[^\n]", history[count].name) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Genre: %[^\n]", history[count].genre) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Price: %lf", &history[count].price) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "Quantity: %d", &history[count].qty) != 1)
    {
      break;
    }
    if (fgets(line, sizeof(line), file) && sscanf(line, "OrderID: %d", &history[count].orderID) != 1)
    {
      break;
    }
    count++;
  }

  fclose(file);
  return count;
}

// Function to display the datapembelian.txt
void displayPurchaseHistory(struct purchaseHistory history[], int count)
{
  if (count == 0)
  {
    printf("You haven't made any purchases\n");
    return;
  }

  printf("Purchase History:\n");
  for (int i = 0; i < count; i++)
  {
    printf("%d. Order ID: %d, Code: %s, Name: %s, Genre: %s, Price: Rp.%.2lf, Quantity: %d\n",
           i + 1, history[i].orderID, history[i].code, history[i].name, history[i].genre, history[i].price, history[i].qty);
  }
}

// Function to delete the purchase history inside datapembelian.txt
void deletePurchaseHistory(struct purchaseHistory books[], int *count)
{
  int index;
  printf("Enter the index of the purchase history to delete (or enter 0 to return to the menu): ");
  scanf("%d", &index);

  if (index == 0)
  {
    return;
  }

  if (index >= 1 && index <= *count)
  {
    for (int i = index - 1; i < *count - 1; i++)
    {
      books[i] = books[i + 1];
    }
    (*count)--;
    printf("Data successfully deleted.\n");
  }
  else
  {
    printf("Invalid index.\n");
  }
}

// Function to delete a book inside the databuku.txt
void deleteBook(struct Book books[], int *count)
{
  int index;
  printf("Enter the index of the book to delete (or enter 0 to return to the menu): ");
  scanf("%d", &index);

  if (index == 0)
  {
    return;
  }

  if (index >= 1 && index <= *count)
  {
    for (int i = index - 1; i < *count - 1; i++)
    {
      books[i] = books[i + 1];
    }
    (*count)--;
    printf("Data successfully deleted.\n");
  }
  else
  {
    printf("Invalid index.\n");
  }
}

// Function to perform a purchase action
// Function to perform a purchase action
void purchaseBook(struct Book books[], int *bookCount, struct purchaseHistory history[], int *historyCount)
{
  int bookIndex;
  printf("Enter the index of the book you want to purchase (or enter 0 to return to the menu): ");
  scanf("%d", &bookIndex);

  if (bookIndex == 0)
  {
    // User chose to return to the menu
    return;
  }

  if (bookIndex >= 1 && bookIndex <= *bookCount)
  {
    int quantity;
    printf("Enter the quantity you want to purchase: ");
    scanf("%d", &quantity);

    if (quantity > 0 && quantity <= books[bookIndex - 1].stock)
    {
      books[bookIndex - 1].stock -= quantity;

      int maxOrderID = 0;
      for (int i = 0; i < *historyCount; i++)
      {
        if (history[i].orderID > maxOrderID)
        {
          maxOrderID = history[i].orderID;
        }
      }

      history[*historyCount].orderID = maxOrderID + 1;
      strcpy(history[*historyCount].code, books[bookIndex - 1].code);
      strcpy(history[*historyCount].name, books[bookIndex - 1].name);
      strcpy(history[*historyCount].genre, books[bookIndex - 1].genre);
      history[*historyCount].price = books[bookIndex - 1].price * quantity;
      history[*historyCount].qty = quantity;
      (*historyCount)++;

      printf("Purchase successful. Total price: Rp.%.2lf\n", history[*historyCount - 1].price);
    }
    else
    {
      printf("Invalid quantity or out of stock.\n");
    }
  }
  else
  {
    printf("Invalid book index.\n");
  }
}

void saveChanges(struct Book books[], int bookCount, struct purchaseHistory history[], int historyCount)
{
  writeBooks(books, bookCount);
  writePurchaseHistory(history, historyCount);
  printf("\n\033[0;32mChanges Saved\033[0m\n");
}

int main()
{
  struct Book *books = malloc(sizeof(struct Book) * 100);
  struct purchaseHistory *pHistory = malloc(sizeof(struct purchaseHistory) * 100);
  int bookCount = readBooks(books, 100);
  int historyCount = readPurchaseHistory(pHistory, 100);

  int option;
  int saved = 1;

  printf("\n\n\033[1m===================BOOK STORE===================\033[0m\n");
  printf("\n\n\033[1;38;5;196m*Changes won't be saved if you don't choose \n'Exit' prior closing the program.\033[0m\n");
  do
  {
    printf("\nMenu:\n");
    printf("1. Input Data\n");
    printf("2. View History\n");
    printf("3. View Book\n");
    printf("4. Purchase\n");
    printf("5. Delete History\n");
    printf("6. Delete Book\n");
    printf("7. Save Changes\n");
    printf("8. Exit\n\n");
    printf("Enter your choice (1 - 8): ");

    scanf("%d", &option);

    switch (option)
    {
    case 1:
      displayBooks(books, bookCount);
      addBook(books, &bookCount);
      saved = 0;
      break;
    case 2:
      displayPurchaseHistory(pHistory, historyCount);
      break;
    case 3:
      if (bookCount > 0)
      {
        displayBooks(books, bookCount);
      }
      else
      {
        printf("There are currently no books in the store, please input more books.\n");
      }
      break;
    case 4:
      displayBooks(books, bookCount);
      purchaseBook(books, &bookCount, pHistory, &historyCount);
      saved = 0;
      break;
    case 5:
      if (historyCount >= 1)
      {
        displayPurchaseHistory(pHistory, historyCount);
        deletePurchaseHistory(pHistory, &historyCount);
      }
      else
      {
        printf("Purchase History is empty.\n");
      }
      saved = 0;
      break;
    case 6:
      if (bookCount >= 1)
      {
        displayBooks(books, bookCount);
        deleteBook(books, &bookCount);
      }
      else
        (
            printf("There are currently no books in the store, please add more book.\n"));
      saved = 0;
      break;
    case 7: // Save Changes
      saveChanges(books, bookCount, pHistory, historyCount);
      saved = 1; // Mark the changes as saved
      break;
    case 8: // Exit
      if (!saved)
      {
        printf("Unsaved changes detected. Do you want to save before exiting? (0 = No | 1 = Yes): ");
        int saveOption;
        scanf("%d", &saveOption);

        if (saveOption == 1)
        {
          saveChanges(books, bookCount, pHistory, historyCount);
        }
      }
      printf("Exiting...\n");
      free(books);
      free(pHistory);
      break;
    default:
      printf("\033[1;38;5;196mInvalid Choices. Please input within range of 1-8.\033[0m\n");
    }
  } while (option != 8);

  return 0;
}