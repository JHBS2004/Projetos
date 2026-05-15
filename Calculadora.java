import java.io.IOException;

public class Calculadora {

    static final int MAX_LINHAS = 3;

    static String display = "0";
    static int selectposX = 0, selectposY = -1;
    static boolean powerOn = true;

    // Lê um único caractere do terminal sem aguardar Enter (modo raw)
    static int getch() throws IOException {
        try {
            String[] cmd = {"/bin/sh", "-c", "stty raw -echo </dev/tty"};
            Runtime.getRuntime().exec(cmd).waitFor();
            int ch = System.in.read();
            String[] restore = {"/bin/sh", "-c", "stty sane </dev/tty"};
            Runtime.getRuntime().exec(restore).waitFor();
            return ch;
        } catch (InterruptedException e) {
            return -1;
        }
    }

    static void interfaceCalculador() {
        // Limpa o terminal
        System.out.print("\033[H\033[2J");
        System.out.flush();

        System.out.println("╔═════════════════════════════╗");
        System.out.println("║ ╭─────────────────────────╮ ║");
        String displayFormatado = String.format("│  %24s  │", display);
        System.out.printf("║ %-25.25s     ║%n", displayFormatado);
        System.out.println("║ ╰─────────────────────────╯ ║");

        if (powerOn) {
            System.out.println("║ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀[ON]▀▀▀▀║");
        } else {
            System.out.println("║ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀[OFF]▀▀▀▀║");
        }

        System.out.println("║ ╭─────────────────────────╮ ║");
        System.out.print("║ |");
        System.out.print((selectposX == 0 && selectposY == -1) ? "[M+]" : " M+ ");
        System.out.print("|");
        System.out.print((selectposX == 1 && selectposY == -1) ? "[M-]" : " M- ");
        System.out.print("|");
        System.out.print((selectposX == 2 && selectposY == -1) ? "[MRC]" : " MRC ");
        System.out.print("|");
        System.out.print((selectposX == 3 && selectposY == -1) ? "[GT]" : " GT ");
        System.out.print("|");
        System.out.print((selectposX == 4 && selectposY == -1) ? "[CE]" : " CE ");
        System.out.println("| ║");
        System.out.println("║ ╰─────────────────────────╯ ║");
        System.out.println("║ ╭───────────╮ ╭───────────╮ ║");

        System.out.print("║ |");
        System.out.print((selectposX == 0 && selectposY == 0) ? "[7]" : " 7 ");
        System.out.print("|");
        System.out.print((selectposX == 1 && selectposY == 0) ? "[8]" : " 8 ");
        System.out.print("|");
        System.out.print((selectposX == 2 && selectposY == 0) ? "[9]" : " 9 ");
        System.out.print("| |");
        System.out.print((selectposX == 3 && selectposY == 0) ? " [÷] " : "  ÷ ");
        System.out.print("|");
        System.out.print((selectposX == 4 && selectposY == 0) ? " [▶] " : " ▶ ");
        System.out.println(" | ║");

        System.out.println("║ |---╋---╋---| |-----╋-----| ║");

        System.out.print("║ |");
        System.out.print((selectposX == 0 && selectposY == 1) ? "[4]" : " 4 ");
        System.out.print("|");
        System.out.print((selectposX == 1 && selectposY == 1) ? "[5]" : " 5 ");
        System.out.print("|");
        System.out.print((selectposX == 2 && selectposY == 1) ? "[6]" : " 6 ");
        System.out.print("| |");
        System.out.print((selectposX == 3 && selectposY == 1) ? "[X]" : " X ");
        System.out.print("|");
        System.out.print((selectposX == 4 && selectposY == 1) ? "[%]" : " % ");
        System.out.println("| ║");

        System.out.println("║ |---╋---╋---| |-----╋-----| ║");

        System.out.print("║ |");
        System.out.print((selectposX == 0 && selectposY == 2) ? "[1]" : " 1 ");
        System.out.print("|");
        System.out.print((selectposX == 1 && selectposY == 2) ? "[2]" : " 2 ");
        System.out.print("|");
        System.out.print((selectposX == 2 && selectposY == 2) ? "[3]" : " 3 ");
        System.out.print("| |");
        System.out.print((selectposX == 3 && selectposY == 2) ? "[-]" : " - ");
        System.out.print("|");
        System.out.print((selectposX == 4 && selectposY == 2) ? "[MU]" : " MU ");
        System.out.println("| ║");

        System.out.println("║ ╰───╋---╋───╯ |-----╋-----| ║");
        System.out.print("║     |");
        System.out.print((selectposX == 1 && selectposY == 3) ? "[0]" : " 0 ");
        System.out.print("|     |");
        System.out.print((selectposX == 2 && selectposY == 3) ? "[+]" : " + ");
        System.out.print("|");
        System.out.print((selectposX == 3 && selectposY == 3) ? "[=]" : " = ");
        System.out.println("| ║");
        System.out.println("║     ╰───╯     ╰───────────╯ ║");
        System.out.println("╚═════════════════════════════╝");
        System.out.println();
    }

    static void processarInput(int tecla) {
        // Liga/desliga
        if (tecla == 'z' || tecla == 'Z') {
            powerOn = !powerOn;
            display = powerOn ? "0" : "OFF";
            return;
        }

        if (!powerOn) return;

        // Confirma seleção com Enter
        if (selectposY >= 0 && (tecla == '\r' || tecla == '\n')) {
            char num = '\0';
            switch (selectposY) {
                case 0: if (selectposX <= 2) num = (char) ('7' + selectposX); break;
                case 1: if (selectposX <= 2) num = (char) ('4' + selectposX); break;
                case 2: if (selectposX <= 2) num = (char) ('1' + selectposX); break;
                case 3: if (selectposX == 1) num = '0'; break;
            }

            if (num != '\0') {
                if (display.equals("0") || display.equals("OFF")) {
                    display = String.valueOf(num);
                } else if (display.length() < 31) {
                    display += num;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        selectposY = -1;
        selectposX = 0;

        while (true) {
            interfaceCalculador();
            int tecla = getch();

            // Trata sequência de escape das setas (27 → 91 → código)
            if (tecla == 27) {
                tecla = getch();
                if (tecla == 91) {
                    tecla = getch();
                }
            }

            switch (tecla) {
                case 'w': case 'W':
                    if (selectposY > -1) selectposY--;
                    break;

                case 's': case 'S':
                    if (selectposY == -1) {
                        selectposY = 0;
                    } else if (selectposY == 2 && selectposX == 0) {
                        selectposY = 3;
                        selectposX = 1;
                    } else if (selectposY == 2 && selectposX == 2) {
                        selectposY = 3;
                        selectposX = 1;
                    } else if (selectposY == 2 && selectposX == 1) {
                        selectposY = 3;
                        selectposX = 1;
                    } else if (selectposY < MAX_LINHAS) {
                        selectposY++;
                    }
                    break;

                case 'a': case 'A':
                    if (selectposY == -1) {
                        if (selectposX > 0) selectposX--;
                    } else if (selectposY == 3) {
                        if (selectposX > 1) selectposX--;
                    } else if (selectposY >= 0) {
                        if (selectposX > 0) selectposX--;
                    }
                    break;

                case 'd': case 'D':
                    if (selectposY == -1) {
                        if (selectposX < 4) selectposX++;
                    } else if (selectposY == 3) {
                        if (selectposX < 3) selectposX++;
                        if (selectposX < 1) selectposX = 1;
                    } else if (selectposY >= 0 && selectposY <= 2) {
                        if (selectposX < 4) selectposX++;
                    }
                    break;

                case 'z': case 'Z':
                    processarInput(tecla);
                    break;

                case '\r': case '\n':
                    processarInput(tecla);
                    break;

                case 'c': case 'C':
                    display = "0";
                    break;
            }
        }
    }
}
