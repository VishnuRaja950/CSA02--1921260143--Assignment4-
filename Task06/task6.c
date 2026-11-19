#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 10
#define MAX_SALES 50
typedef struct { int day, month, year; } Date;
typedef enum { PACKAGED, COOKED, COMBO } ItemKind;
typedef struct { Date expiry; } PackagedInfo;
typedef struct { int hour, minute; } CookedInfo;
typedef struct { int component_ids[3]; int count; } ComboInfo;
typedef struct { int id; char name[30]; float price; int stock; ItemKind kind; union { PackagedInfo packaged; CookedInfo cooked; ComboInfo combo; } data; } Item;
typedef struct { int id, quantity; float revenue; } Sale;
int find_item(const Item items[], int n, int id) {
    for (int i = 0; i < n; ++i) if (items[i].id == id) return i;
    return -1;
}
int record_sale(Item items[], int n, int id, int quantity, Sale sales[], int *count) {
    int pos;
    if (!items || !sales || !count || quantity <= 0 || *count >= MAX_SALES) return 0;
    pos = find_item(items, n, id);
    if (pos < 0 || quantity > items[pos].stock) return 0;
    sales[*count].id = id;
    sales[*count].quantity = quantity;
    sales[*count].revenue = quantity * items[pos].price;
    items[pos].stock -= quantity;
    ++(*count);
    return 1;
}
/* Dates in this demonstration are in the same month and year. */
int expires_within_two_days(Date today, Date expiry) {
    if (today.year != expiry.year || today.month != expiry.month) return 0;
    return expiry.day >= today.day && expiry.day <= today.day + 2;
}
void sort_summary(Sale sales[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int best = i;
        for (int j = i + 1; j < n; ++j) if (sales[j].revenue > sales[best].revenue) best = j;
        if (best != i) { Sale t = sales[i]; sales[i] = sales[best]; sales[best] = t; }
    }
}
int main(void) {
    Item items[3] = {{1, "Milk", 30.0f, 5, PACKAGED, {.packaged = {{20, 11, 2026}}}}, {2, "Sandwich", 50.0f, 4, COOKED, {.cooked = {10, 30}}}, {3, "Juice", 40.0f, 2, PACKAGED, {.packaged = {{22, 11, 2026}}}}};
    Sale sales[MAX_SALES]; int count = 0;
    Date today = {19, 11, 2026};
    if (record_sale(items, 3, 1, 2, sales, &count)) puts("Sale recorded: Milk x2 = Rs.60.00");
    if (!record_sale(items, 3, 3, 5, sales, &count)) puts("Sale rejected: insufficient stock for Juice");
    if (expires_within_two_days(today, items[0].data.packaged.expiry)) puts("Expiry warning: Milk expires within two days");
    if (record_sale(items, 3, 2, 1, sales, &count)) puts("Sale recorded: Sandwich x1 = Rs.50.00");
    sort_summary(sales, count);
    puts("Daily summary (highest revenue first):");
    for (int i = 0; i < count; ++i) printf("Item %d: quantity %d, revenue Rs.%.2f\n", sales[i].id, sales[i].quantity, sales[i].revenue);
    printf("Milk stock remaining: %d\n", items[0].stock);
    return 0;
}
