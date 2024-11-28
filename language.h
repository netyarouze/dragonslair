
/* Available Languages

0: English
1: Japanese
2: Spanish
3: French
4: Italian
5: German
6: Portuguese
7: Turkish

*/

#ifdef OPTIONS_C

char Language[8][10] = {
"English",
"",// Japanese
"Español",
"Français",
"Italiano",
"Deutsch",
"Português",
"Türkçe"
};

short SelectedLanguage = 0;

char TXT_PressStart[8][18] = {
"Press Start",
"Press Start",// Japanese use English in this case.
"Pulsa Start",
"Appuyez Sur Start",
"Premi Start",
"Start Drücken",
"Aperte Start",
"Start A Basin",
};

char TXT_NewGame[8][16] = {
"New Game",
"¦™¾±",
"Comenzar",
"Nouvelle Partie",
"Nuovo Gioco",
"Neues Spiel",
"Novo Jogo",
"Yenï Oyun",
};

char TXT_Options[8][15] = {
"Options",
"•¬¿œ½",
"Opciones",
"Options",
"Opzioni",
"Optionen",
"Opções",
"Ayarlar",
};

char TXT_Difficulty[8][19] = {
"Difficulty",
"º­¾¹",
"Dificultad",
"Difficulté",
"Difficoltà",
"Schwierigkeitsgrad",
"Dificuldade",
"Zorluk",
};

char TXT_Vibration[8][15] = {
"Vibration",
"ª¾’¬¾ºœ½",
"Vibración",
"Vibrations",
"Vibrazione",
"Vibration",
"Vibração",
"Titreÿim", // 'ÿ' is actually displayed as a lowercase 's' with cedilla.
};

char TXT_On[8][15] = {
"On",
"On",
"Sí",
"Oui",//Activée / Avec
"On",
"Ein",
"On",
"Açik",
};

char TXT_Off[8][15] = {
"Off",
"Off",
"No",
"Non",//Désactivée / Sans
"Off",
"Aus",
"Off",
"Kapali",
};

char TXT_Easy[8][15] = {
"Easy",
"ôÛÜÒ",
"Fácil",
"Facile",
"Facile",
"Leicht",
"Fácil",
"Kolay",
};

char TXT_Normal[8][15] = {
"Normal",
"ìâÓ",
"Normal",
"Normal",
"Normale",
"Normal",
"Normal",
"Normal",
};

char TXT_Hard[8][15] = {
"Hard",
"ñİ¾ÖÜÒ",
"Difícil",
"Dur",
"Difficile",
"Schwierig",
"Difícil",
"Zor",
};

char TXT_Lives[8][15] = {
"Lives",
"£¾˜ ", // Dexter instead of Lives/raifu.
"Vidas",
"Vies",
"Vite",
"Leben",
"Vidas",
"Hayat",
};

char TXT_Continue[8][15] = {
"Continue?",
"¸¤·’", // Japanese
"¿Continuar?",
"Continuer?", // French
"Continuare?", // Italian
"Fortsetzen?", // German
"Continuar?", // Portuguese
"Devam etmek?", // Turkish
};

char TXT_Credits[8][15] = {
"Credits",
"˜»œ¾¤", // Japanese
"Créditos",
"Crédits", // French
"Crediti", // Italian
"Kredite", // German
"Créditos", // Portuguese
"Kredi", // Turkish
};

char TXT_Up[8][15] = {
"Up",
"ÓÔ", // Japanese
"Arriba",
"Haut", // French
"Su", // Italian
"Hoch", // German
"Cima", // Portuguese
"Yukari", // Turkish
};

char TXT_Down[8][15] = {
"Down",
"Üà", // Japanese
"Abajo",
"Bas", // French
"Giù", // Italian
"Runter", // German
"Baixo", // Portuguese
"Aÿaşı", // Turkish ( ÿ is displayed as a lowercase 's' with cedilla).
}; // ş is displayed as a lowercase 'g' with breve.
// ı is displayed as a lowercase 'i' without dot.

char TXT_Left[8][15] = {
"Left",
"ëà¾ø", // Japanese
"Izquierda",
"Gauche", // French
"Sinistra", // Italian
"Links", // German
"Esquerda", // Portuguese
"Sol", // Turkish
};

char TXT_Right[8][15] = {
"Right",
"ğ×¾", // Japanese
"Derecha",
"Droite", // French
"Destra", // Italian
"Rechts", // German
"Direita", // Portuguese
"Saş", // Turkish ( ş is displayed as a lowercase 'g' with breve).
};

char TXT_Sword[8][15] = {
"Sword",
"Ùı", // Japanese
"Espada",
"Épée", // French
"Spada", // Italian
"Schwert", // German
"Espada", // Portuguese
"kılıç", // Turkish ( ı is displayed as a lowercase 'i' without dot).
};

char TXT_Pause[8][15] = {
"Pause",
"×ÍÓÜ", // Japanese
"Pausa",
"Pause", // French
"Pausa", // Italian
"Pause", // German
"Pausa", // Portuguese
"Duraklat", // Turkish
};

char TXT_Energize[8][15] = {
"Energize",
"Energize", // Japanese
"Energize",
"Energize", // French
"Energize", // Italian
"Energize", // German
"Energize", // Portuguese
"Energize", // Turkish
};


char TXT_Mistakes[8][15] = {
"Mistakes",
"°", // Japanese
"Errores",
"Erreurs", // French
"Sbagli", // Italian
"Fehler", // German
"Erros", // Portuguese
"Hata", // Turkish
};

char TXT_Retries[8][18] = {
"Retries",
"¸¤·’", // Japanese
"Reintentos",
"Tentatives", // French
"Tentativi", // Italian
"Wiederholungen", // German
"Tentativas", // Portuguese
"Devamlar", // Turkish 
};

char TXT_Ending[8][15] = {
"Ending",
"”½£¾ˆ½˜", // Japanese
"Final",
"Fin", // French
"Fine", // Italian
"Ende", // German
"Final", // Portuguese
"Son", // Turkish
};

char TXT_Score[8][15] = {
"Score",
"š‘", // Japanese
"Puntuación",
"Score", // French
"Punteggio", // Italian
"Punktzahl", // German
"Pontuação", // Portuguese
"Son", // Turkish
};

char TXT_Perfect[8][15] = {
"Perfect!",
"ª¾¡¸!", // Japanese
"¡Perfecto!",
"Parfait !", // French
"Perfetto!", // Italian
"Perfekt!", // German
"Perfeito!", // Portuguese
"Kusursuz!", // Turkish
};

char TXT_ScreenAdjust[8][20] = {
"Screen Adjust",
"£¾ˆ¬¿º’", // Japanese
"Ajustar Pantalla",
"Réglage de l'écran", // French
"Correzione Schermo", // Italian
"Bildschirm Anpassen", // German
"Ajuste De Tela", // Portuguese
"Ekran Ayari", // Turkish
};

char Main_Menu_Entries[2][16];
char Options_Menu_Entries[3][20];
char Difficulty_Entries[3][15];
char OnOff_Entries[2][15];
char Move_Entries[6][15];

#else

extern char Language[8][10];
extern short SelectedLanguage;
extern char TXT_PressStart[8][18];
extern char TXT_Lives[8][15];
extern char TXT_Continue[8][15];
extern char TXT_Credits[8][15];
extern char TXT_Up[8][15];
extern char TXT_Down[8][15];
extern char TXT_Left[8][15];
extern char TXT_Right[8][15];
extern char TXT_Sword[8][15];
extern char Move_Entries[6][15];
extern char TXT_Pause[8][15];
extern char OnOff_Entries[2][15];
extern char TXT_Energize[8][15];
extern char TXT_Mistakes[8][15];
extern char TXT_Retries[8][18];
extern char TXT_Ending[8][15];
extern char TXT_Score[8][15];
extern char TXT_Perfect[8][15];
extern char TXT_ScreenAdjust[8][16];
extern char TXT_Difficulty[8][19];
extern char Difficulty_Entries[3][15];
#endif