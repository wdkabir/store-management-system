#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 100
#define FILE_NAME "products.txt"

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

int isProductIdValid(int id) {
    // Check if the ID is positive
    if (id <= 0) {
        printf("Invalid product ID. Please enter a positive integer.\n");
        return 0;
    }

    // Check if the ID is unique
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("Product with the same ID already exists. Please enter a different ID.\n");
            return 0;
        }
    }

    return 1;
}

int isProductNameValid(const char* name) {
    // Check if the name is not empty
    if (strlen(name) == 0) {
        printf("Product name cannot be empty. Please enter a valid name.\n");
        return 0;
    }

    return 1;
}

int isProductPriceValid(float price) {
    // Check if the price is positive
    if (price <= 0) {
        printf("Invalid product price. Please enter a positive value.\n");
        return 0;
    }

    return 1;
}

int isProductQuantityValid(int quantity) {
    // Check if the quantity is non-negative
    if (quantity < 0) {
        printf("Invalid product quantity. Please enter a non-negative value.\n");
        return 0;
    }

    return 1;
}

void saveProductsToFile() {
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }

    fclose(file);
    printf("Product data saved to file.\n");
}

void loadProductsFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    while (productCount < MAX_PRODUCTS && fscanf(file, "%d,%[^,],%f,%d\n", &products[productCount].id, products[productCount].name, &products[productCount].price, &products[productCount].quantity) == 4) {
        productCount++;
    }

    fclose(file);
}

void createProduct() {
    if (productCount == MAX_PRODUCTS) {
        printf("Maximum number of products reached.\n");
        return;
    }

    Product newProduct;
    printf("Enter product ID: ");
    scanf("%d", &newProduct.id);

    if (!isProductIdValid(newProduct.id)) {
        return;
    }

    printf("Enter product name: ");
    scanf("%s", newProduct.name);

    if (!isProductNameValid(newProduct.name)) {
        return;
    }

    printf("Enter product price: ");
    scanf("%f", &newProduct.price);

    if (!isProductPriceValid(newProduct.price)) {
        return;
    }

    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);

    if (!isProductQuantityValid(newProduct.quantity)) {
        return;
    }

    products[productCount] = newProduct;
    productCount++;

    saveProductsToFile(); // Save the updated product data to the file

    printf("Product added successfully.\n");
}

void readProducts() {
    if (productCount == 0) {
        printf("No products available.\n");
        return;
    }

    printf("Product List:\n");
    printf("+-------+----------------------+------------+--------------+\n");
    printf("| %-5s | %-20s | %-14s | %-8s |\n", "ID", "Name", "Price(Taka)", "Quantity");
    printf("+-------+----------------------+------------+--------------+\n");

    for (int i = 0; i < productCount; i++) {
        printf("| %-5d | %-20s | %-9.2f Taka | %-8d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }

    printf("+-------+----------------------+------------+--------------+\n");
}

void updateProduct() {
    int productId;
    printf("Enter the ID of the product to update: ");
    scanf("%d", &productId);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            printf("Enter new name: ");
            scanf("%s", products[i].name);

            if (!isProductNameValid(products[i].name)) {
                return;
            }

            printf("Enter new price: ");
            scanf("%f", &products[i].price);

            if (!isProductPriceValid(products[i].price)) {
                return;
            }

            printf("Enter new quantity: ");
            scanf("%d", &products[i].quantity);

            if (!isProductQuantityValid(products[i].quantity)) {
                return;
            }

            saveProductsToFile(); // Save the updated product data to the file

            printf("Product updated successfully.\n");
            readProducts(); // Display the updated product list
            return;
        }
    }

    printf("Product not found.\n");
}

void deleteProduct() {
    int productId;
    printf("Enter the ID of the product to delete: ");
    scanf("%d", &productId);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;

            saveProductsToFile(); // Save the updated product data to the file

            printf("Product deleted successfully.\n");
            readProducts(); // Display the updated product list
            return;
        }
    }

    printf("Product not found.\n");
}

void searchProduct() {
    int productId;
    printf("Enter the ID of the product to search: ");
    scanf("%d", &productId);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            printf("Product found:\n");
            printf("| %-5s | %-20s | %-14s | %-8s |\n", "ID", "Name", "Price(Taka)", "Quantity");
            printf("+-------+----------------------+------------+--------------+\n");
            printf("| %-5d | %-20s | %-9.2f Taka | %-8d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
            printf("+-------+----------------------+------------+--------------+\n");
            return;
        }
    }

    printf("Product not found.\n");
}

int main() {
    loadProductsFromFile(); // Load the product data from the file

    int choice;

    while (1) {
        printf("\nStore Management System By Kabir\n");
        printf("1. Add Product\n");
        printf("2. List Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createProduct();
                readProducts(); // Display the updated product list
                break;
            case 2:
                readProducts();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                searchProduct();
                break;
            case 6:
                printf("Exiting...\n");
                saveProductsToFile(); // Save the product data before exiting
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
