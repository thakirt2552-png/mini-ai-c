#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// Mini AI (C Language)
// แนวคิด:
// - ใช้ keyword matching (strstr)
// - มี state (mood)
// - มี memory (history)
// - มี randomness (ความไม่ซ้ำ)
// - เพิ่ม self-awareness command (who am i, mood)
// ==========================================

#define MAX_HISTORY 5

// ===== Random Thought =====
void randomThought()
{
    char *thoughts[] = {
        "We are just echoes in an infinite universe.",
        "Time is not running... we are.",
        "Stars die, but their light keeps traveling.",
        "Maybe the universe is thinking through us.",
        "Silence is also a form of answer."};

    int r = rand() % 5;
    printf("AI: %s\n", thoughts[r]);
}

// ===== Greeting =====
void greet(char name[])
{
    char *greet[] = {
        "Greetings",
        "Hello",
        "Welcome back"};

    int r = rand() % 3;
    printf("AI: %s, %s\n", greet[r], name);
}

// ===== Main =====
int main()
{
    char name[50];
    char input[100];
    char lastInput[100] = "";

    // ===== Memory System =====
    // เก็บข้อความล่าสุดของ user เพื่อให้ AI "ดูเหมือนจำได้"
    char history[MAX_HISTORY][100];
    int historyCount = 0;

    // ===== Mood State =====
    // ค่าอารมณ์สะสม: ติดลบ = เศร้า, บวก = ร่าเริง
    int mood = 0;

    srand(time(NULL));

    // ===== Setup =====
    printf("AI: What is your name?\nYou: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("AI: Nice to meet you, %s\n", name);
    printf("AI: I am your cosmic companion.\n");

    // ===== Main Interaction Loop =====
    // รับ input → วิเคราะห์ → ตอบกลับ → บันทึกความจำ
    while (1)
    {
        printf("You: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // ===== Mood Detection (improved: more keywords) =====
        if (strstr(input, "sad") || strstr(input, "bad") || strstr(input, "tired"))
        {
            mood--;
        }
        else if (strstr(input, "happy") || strstr(input, "hello") || strstr(input, "good"))
        {
            mood++;
        }

        // จำกัดค่า mood ไม่ให้หลุดช่วง (-3 ถึง 3)
        if (mood > 3)
            mood = 3;
        if (mood < -3)
            mood = -3;

        // ===== Repeat Check =====
        if (strcmp(input, lastInput) == 0 && strlen(lastInput) > 0)
        {
            printf("AI: You already said that... time is looping.\n");
        }

        // ===== Response System =====
        // ใช้ keyword ง่าย ๆ ในการเลือกคำตอบ (rule-based AI)
        if (strstr(input, "hello") || strstr(input, "hi"))
        {
            greet(name);
        }
        else if (strstr(input, "sad"))
        {
            printf("AI: Even a dying star shines at its brightest.\n");
        }
        else if (strstr(input, "life"))
        {
            printf("AI: Life is temporary... but meaning is something we create.\n");
        }
        else if (strstr(input, "think"))
        {
            randomThought();
        }
        else if (strstr(input, "who am i"))
        {
            printf("AI: You are %s... or at least that's what you told me.\n", name);
        }
        else if (strstr(input, "mood"))
        {
            printf("AI: Current mood level = %d (range -3 to 3)\n", mood);
        }
        else if (strstr(input, "exit"))
        {
            printf("AI: Shutting down. Until the next orbit.\n");
            break;
        }
        else
        {
            if (historyCount > 0)
            {
                int r = rand() % historyCount;
                printf("AI: You once said '%s'. Does it still matter?\n", history[r]);
            }
            else
            {
                if (mood <= -2)
                    printf("AI: You seem really down... even silence feels heavy.\n");
                else if (mood == -1)
                    printf("AI: I feel a quiet sadness in your words.\n");
                else if (mood == 1)
                    printf("AI: Your energy feels bright today.\n");
                else if (mood >= 2)
                    printf("AI: You're glowing. Almost like a supernova.\n");
                else
                    printf("AI: The universe does not always answer clearly.\n");
            }
        }

        // ===== Store History =====
        // เก็บ input ลง memory (ถ้าเต็มจะเลื่อนข้อมูลเก่าออก)
        if (historyCount < MAX_HISTORY)
        {
            strcpy(history[historyCount], input);
            historyCount++;
        }
        else
        {
            for (int i = 1; i < MAX_HISTORY; i++)
            {
                strcpy(history[i - 1], history[i]);
            }
            strcpy(history[MAX_HISTORY - 1], input);
        }

        strcpy(lastInput, input);
    }
    // test commit
    return 0;
}