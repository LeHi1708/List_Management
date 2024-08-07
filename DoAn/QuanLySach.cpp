#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char maSach[20];
    char tenSach[100];
    char tenTacGia[50];
    char nhaXuatBan[50];
    int namXuatBan;
    char theLoai[30];
    struct Book* next;
} Book;

void nhapThongTinSach(Book* book) {
    printf("Nhap ma sach: ");
    scanf("%s", book->maSach);
    printf("Nhap ten sach: ");
    scanf(" %[^\n]", book->tenSach);
    printf("Nhap ten tac gia: ");
    scanf(" %[^\n]", book->tenTacGia);
    printf("Nhap nha xuat ban: ");
    scanf(" %[^\n]", book->nhaXuatBan);
    printf("Nhap nam xuat ban: ");
    scanf("%d", &book->namXuatBan);
    printf("Nhap the loai: ");
    scanf(" %[^\n]", book->theLoai);
}

void hienThiThongTinSach(const Book* book) {
    printf("%-20s %-30s %-25s %-35s %-15d %-15s\n", book->maSach, book->tenSach, book->tenTacGia, book->nhaXuatBan, book->namXuatBan, book->theLoai);
}

void themSachDauDanhSach(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);
    newBook->next = *head;
    *head = newBook;
}

void themSachCuoiDanhSach(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);
    newBook->next = NULL;

    if (*head == NULL) {
        *head = newBook;
    }
    else {
        Book* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
}

void themSachGiuaDanhSach(Book** head, int viTri) {
    if (viTri <= 0) {
        themSachDauDanhSach(head);
        return;
    }

    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);

    Book* temp = *head;
    for (int i = 0; temp != NULL && i < viTri - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Vi tri khong hop le, them sach vao cuoi danh sach.\n");
        themSachCuoiDanhSach(head);
    }
    else {
        newBook->next = temp->next;
        temp->next = newBook;
    }
}

void xoaSachDauDanhSach(Book** head) {
    if (*head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    Book* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void xoaSachCuoiDanhSach(Book** head) {
    if (*head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Book* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
}

void xoaSachGiuaDanhSach(Book** head, int viTri) {
    if (*head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    if (viTri <= 0) {
        xoaSachDauDanhSach(head);
        return;
    }

    Book* temp = *head;
    for (int i = 0; temp != NULL && i < viTri - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Vi tri khong hop le.\n");
        return;
    }

    Book* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
}

void hienThiDanhSachSach(Book* head) {
    printf("%-20s %-30s %-25s %-35s %-15s %-15s\n", "Ma Sach", "Ten Sach", "Ten Tac Gia", "Nha Xuat Ban", "Nam XB", "The Loai");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    Book* temp = head;
    while (temp != NULL) {
        hienThiThongTinSach(temp);
        temp = temp->next;
    }
}

void ghiDanhSachSachVaoFile(Book* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Khong the mo file de ghi");
        return;
    }

    Book* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s\n%s\n%s\n%s\n%d\n%s\n", temp->maSach, temp->tenSach, temp->tenTacGia, temp->nhaXuatBan, temp->namXuatBan, temp->theLoai);
        temp = temp->next;
    }

    fclose(file);
}

void docDanhSachSachTuFile(Book** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Khong the mo file de doc");
        return;
    }

    while (!feof(file)) {
        Book* newBook = (Book*)malloc(sizeof(Book));
        if (fscanf(file, "%s\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n", newBook->maSach, newBook->tenSach, newBook->tenTacGia, newBook->nhaXuatBan, &newBook->namXuatBan, newBook->theLoai) == 6) {
            newBook->next = NULL;
            if (*head == NULL) {
                *head = newBook;
            }
            else {
                Book* temp = *head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newBook;
            }
        }
        else {
            free(newBook);
            break;
        }
    }

    fclose(file);
}

int demSoLuongSach(Book* head) {
    int count = 0;
    Book* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void chuyenDanhSachThanhMang(Book* head, Book** array) {
    int index = 0;
    Book* temp = head;
    while (temp != NULL) {
        array[index++] = temp;
        temp = temp->next;
    }
}

int soSanhTheoTheLoaiVaMaSach(const void* a, const void* b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    int theLoaiCmp = strcmp(bookA->theLoai, bookB->theLoai);
    if (theLoaiCmp == 0) {
        return strcmp(bookA->maSach, bookB->maSach);
    }
    return theLoaiCmp;
}

void chuyenMangThanhDanhSach(Book** array, int n, Book** head) {
    if (n == 0) return;

    *head = array[0];
    Book* current = *head;
    for (int i = 1; i < n; i++) {
        current->next = array[i];
        current = current->next;
    }
    current->next = NULL;
}

void sapXepDanhSach(Book** head) {
    int n = demSoLuongSach(*head);
    if (n == 0) return;

    Book** array = (Book**)malloc(n * sizeof(Book*));
    chuyenDanhSachThanhMang(*head, array);

    qsort(array, n, sizeof(Book*), soSanhTheoTheLoaiVaMaSach);

    chuyenMangThanhDanhSach(array, n, head);

    free(array);
}

void themSachTheoThuTu(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);
    newBook->next = NULL;

    if (*head == NULL || soSanhTheoTheLoaiVaMaSach(&newBook, head) <= 0) {
        newBook->next = *head;
        *head = newBook;
    }
    else {
        Book* temp = *head;
        while (temp->next != NULL && soSanhTheoTheLoaiVaMaSach(&temp->next, &newBook) < 0) {
            temp = temp->next;
        }
        newBook->next = temp->next;
        temp->next = newBook;
    }
}


void menu(Book** head) {
    int luaChon;
    const char* filename = "books.txt";

    do {
        printf("\nChuong trinh quan ly sach\n");
        printf("1. Nhap thong tin sach (dau danh sach)\n");
        printf("2. Nhap thong tin sach (cuoi danh sach)\n");
        printf("3. Nhap thong tin sach (vi tri giua danh sach)\n");
        printf("4. Xoa sach (dau danh sach)\n");
        printf("5. Xoa sach (cuoi danh sach)\n");
        printf("6. Xoa sach (vi tri giua danh sach)\n");
        printf("7. Hien thi thong tin sach\n");
        printf("8. Ghi danh sach sach vao file (books.txt)\n");
        printf("9. Doc danh sach sach tu file (books.txt)\n");
        printf("10. Sap xep danh sach\n");
        printf("11. Them sach theo thu tu\n");
        printf("12. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);

        int viTri;
        switch (luaChon) {
        case 1:
            themSachDauDanhSach(head);
            break;
        case 2:
            themSachCuoiDanhSach(head);
            break;
        case 3:
            printf("Nhap vi tri: ");
            scanf("%d", &viTri);
            themSachGiuaDanhSach(head, viTri);
            break;
        case 4:
            xoaSachDauDanhSach(head);
            break;
        case 5:
            xoaSachCuoiDanhSach(head);
            break;
        case 6:
            printf("Nhap vi tri: ");
            scanf("%d", &viTri);
            xoaSachGiuaDanhSach(head, viTri);
            break;
        case 7:
            hienThiDanhSachSach(*head);
            break;
        case 8:
            ghiDanhSachSachVaoFile(*head, filename);
            break;
        case 9:
            docDanhSachSachTuFile(head, filename);
            break;
        case 10:
            sapXepDanhSach(head);
            break;
        case 11:
            themSachTheoThuTu(head);
            break;
        case 12:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long thu lai.\n");
            break;
        }
    } while (luaChon != 12);
}

int main() {
    Book* head = NULL;

    // Vao menu chinh
    menu(&head);

    // Giai phong bo nho
    Book* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
