#include <GL/glut.h>

// Variabel untuk mengatur sudut rotasi berdasarkan interaksi mouse
float rotateX = 0.0f, rotateY = 0.0f;
int lastMouseX, lastMouseY;
bool isDragging = false; // Untuk mengecek apakah mouse sedang men-drag

// Fungsi inisialisasi
void init() {
    // Mengatur warna latar belakang menjadi hitam
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Mengaktifkan depth testing
    glEnable(GL_DEPTH_TEST);

    // Mengatur proyeksi perspektif
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menggambar tombol (sphere) 3D
void drawButton(float x, float y, float z, float radius, float r, float g, float b) {
    // Set warna tombol sesuai parameter (RGB)
    glColor3f(r, g, b);

    // Menyimpan matriks saat ini
    glPushMatrix();

    // Memindahkan tombol ke posisi yang diinginkan
    glTranslatef(x, y, z);

    // Perbesar ukuran tombol dengan radius yang lebih besar
    glScalef(2.0f, 2.0f, 2.0f); // Membuat tombol lebih besar

    // Menggambar tombol sebagai sebuah sphere
    glutSolidSphere(radius * 1.5f, 30, 30); // Radius sedikit lebih besar

    // Mengembalikan matriks sebelumnya
    glPopMatrix();
}

// Fungsi untuk menggambar lubang kunci (silinder)
void drawKeyHole(float x, float y, float z, float radius, float height) {
    // Set warna lubang kunci
    glColor3f(0.4f, 0.4f, 0.4f); // Abu-abu gelap

    // Menyimpan matriks saat ini
    glPushMatrix();

    // Memindahkan lubang kunci ke posisi yang diinginkan
    glTranslatef(x, y, z);

    // Menggambar silinder (lubang kunci) dengan ukuran lebih kecil dan pendek
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius * 2.0f, radius * 2.0f, height * 0.5f, 30, 30); // Radius lebih besar, tinggi lebih pendek

    // Mengembalikan matriks sebelumnya
    glPopMatrix();
}

// Fungsi untuk menggambar panel switch listrik 3D
void drawPanel() {
    // Menggambar bagian utama panel (kubus tebal 3D)
    glPushMatrix();

    // Warna panel: abu-abu muda (sesuai gambar)
    glColor3f(0.9f, 0.9f, 0.9f);

    // Skala untuk membuat panel lebih tebal
    glScalef(6.0f, 8.0f, 2.0f); // Membuat kubus panel lebih tebal (dimensi lebih besar pada sumbu Z)
    glutSolidCube(5.0);  // Menggambar panel utama

    glPopMatrix();

    // Menggambar tombol-tombol pada panel dengan jarak yang lebih jauh
    // Tombol Hijau (Kiri Bawah)
    drawButton(-4.5f, -4.5f, 5.0f, 0.5f, 0.0f, 1.0f, 0.0f); // Hijau
    // Tombol Hijau (Kiri Atas)
    drawButton(-4.5f, 4.5f, 5.0f, 0.5f, 0.0f, 1.0f, 0.0f); // Hijau

    // Tombol Kuning (Tengah Atas)
    drawButton(0.0f, 4.5f, 5.0f, 0.5f, 1.0f, 1.0f, 0.0f); // Kuning

    // Tombol Kuning (Tengah Bawah)
    drawButton(0.0f, -4.5f, 5.0f, 0.5f, 1.0f, 1.0f, 0.0f); // Kuning

    // Tombol Merah (Kanan Atas)
    drawButton(4.5f, 4.5f, 5.0f, 0.5f, 1.0f, 0.0f, 0.0f); // Merah

    // Tombol Merah (Kanan Bawah)
    drawButton(4.5f, -4.5f, 5.0f, 0.5f, 1.0f, 0.0f, 0.0f); // Merah

    // Menggambar lubang kunci dengan posisi lebih jauh ke bawah agar tidak bertabrakan dengan tombol
    drawKeyHole(-5.5f, -6.5f, 5.0f, 0.3f, 0.5f); // Lubang kunci di bagian kiri bawah
}

// Fungsi untuk menggambar teks
void drawText(float x, float y, float z, const char* text) {
    glRasterPos3f(x, y, z);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

// Fungsi untuk menggambar setiap frame
void display() {
    // Membersihkan buffer warna dan depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Mereset matriks model-view
    glLoadIdentity();

    // Mengatur kamera menggunakan gluLookAt untuk efek zoom out
    gluLookAt(0.0, 10.0, 40.0,   // Posisi kamera lebih jauh untuk zoom out
        0.0, 0.0, 0.0,     // Titik yang dilihat
        0.0, 1.0, 0.0);    // Arah atas

    // Mengatur rotasi interaktif objek berdasarkan input mouse
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Rotasi pada sumbu X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotasi pada sumbu Y

    // Menggambar panel switch listrik 3D
    drawPanel();

    // Menggambar teks nama kelompok di atas panel
    drawText(-5.0f, 8.0f, 5.5f, "Kelompok 10 :");
    drawText(-5.0f, 7.0f, 5.5f, "Fina Salsabila Pramudita (5223600006)");
    drawText(-5.0f, 6.0f, 5.5f, "Rayhan Elmo Athalah Saputra (5223600027)");

    // Memaksa rendering adegan
    glFlush();
    glutSwapBuffers();
}

// Fungsi untuk menangani input mouse (klik dan drag)
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Menandakan mulai drag
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else {
            // Menandakan berhenti drag
            isDragging = false;
        }
    }
}

// Fungsi untuk menangani pergerakan mouse ketika drag
void mouseMotion(int x, int y) {
    if (isDragging) {
        // Hitung perbedaan posisi mouse
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        // Update sudut rotasi berdasarkan pergerakan mouse
        rotateX += (float)dy * 0.5f;
        rotateY += (float)dx * 0.5f;

        // Simpan posisi mouse terbaru
        lastMouseX = x;
        lastMouseY = y;

        // Minta redisplay untuk menggambar ulang frame
        glutPostRedisplay();
    }
}

// Fungsi utama
int main(int argc, char** argv) {
    // Inisialisasi GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); // Ukuran jendela
    glutCreateWindow("3D Panel Switch Listrik dengan Nama Kelompok");

    // Memanggil fungsi inisialisasi
    init();

    // Menetapkan fungsi display sebagai callback untuk menggambar
    glutDisplayFunc(display);

    // Menetapkan fungsi mouse untuk menangani klik dan drag
    glutMouseFunc(mouseButton);

    // Menetapkan fungsi motion untuk menangani pergerakan mouse ketika drag
    glutMotionFunc(mouseMotion);

    // Loop utama GLUT
    glutMainLoop();
    return 0;
}
