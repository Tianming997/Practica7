#include <Arduino.h>
#include <driver/i2s.h>

// ---------------- PINS ----------------
#define MIC_WS    26 
#define MIC_SD    25 
#define MIC_SCK   33 

#define SPK_WS    14
#define SPK_DOUT  27
#define SPK_BCLK  12

// ---------------- AUDIO CONFIG ----------------
#define SAMPLE_RATE 16000
#define RECORD_TIME 3
#define BUFFER_SAMPLES (SAMPLE_RATE * RECORD_TIME)

// buffer en RAM
int16_t* voice_buffer = NULL;
size_t bytes_read = 0;

// ---------------- I2S MIC ----------------
void setupMic() {

    i2s_config_t mic_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),

        // ✔ 16-bit estable
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,

        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,

        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
        .use_apll = false
    };

    i2s_driver_install(I2S_NUM_0, &mic_config, 0, NULL);

    i2s_pin_config_t mic_pins = {
        .bck_io_num = MIC_SCK,
        .ws_io_num = MIC_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = MIC_SD
    };

    i2s_set_pin(I2S_NUM_0, &mic_pins);
}

// ---------------- I2S SPEAKER ----------------
void setupSpeaker() {

    i2s_config_t spk_config = {#include <Arduino.h>
#include <driver/i2s.h>

// ---------------- PINS ----------------
#define MIC_WS    26 
#define MIC_SD    25 
#define MIC_SCK   33 

#define SPK_WS    14
#define SPK_DOUT  27
#define SPK_BCLK  12
#include <Arduino.h>
#include <driver/i2s.h>

// --- PINES ---
#define MIC_WS    26 
#define MIC_SD    25 
#define MIC_SCK   33 

#define SPK_WS    14
#define SPK_DOUT  27
#define SPK_BCLK  12

// 🔥 CAMBIA ESTO PARA PROBAR
#define TEST_RATE 1600   // prueba: 8000 / 12000 / 16000 / 22050

#define RECORD_TIME 2
#define BUFFER_SAMPLES (TEST_RATE * RECORD_TIME)

int16_t* voice_buffer = NULL;
size_t total_bytes = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.print("TEST SAMPLE RATE: ");
    Serial.println(TEST_RATE);

    voice_buffer = (int16_t*) malloc(BUFFER_SAMPLES * sizeof(int16_t));

    if (!voice_buffer) {
        Serial.println("ERROR RAM");
        while (1);
    }

    // ---------------- MIC ----------------
    i2s_config_t mic_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = TEST_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .use_apll = false
    };

    i2s_driver_install(I2S_NUM_0, &mic_config, 0, NULL);

    i2s_pin_config_t mic_pins = {
        .bck_io_num = MIC_SCK,
        .ws_io_num = MIC_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = MIC_SD
    };

    i2s_set_pin(I2S_NUM_0, &mic_pins);

    Serial.println("Grabando...");

    i2s_read(I2S_NUM_0,
             voice_buffer,
             BUFFER_SAMPLES * sizeof(int16_t),
             &total_bytes,
             portMAX_DELAY);

    Serial.println("Grabación OK");

    // ---------------- DEBUG INTENSO ----------------
    Serial.println("\n--- BUFFER (primeros 200 valores) ---");

    int max_print = 200;
    for (int i = 0; i < max_print && i < BUFFER_SAMPLES; i++) {

        Serial.print(voice_buffer[i]);
        Serial.print(",");

        if (i % 20 == 0) Serial.println();
    }

    Serial.println("\n--- FIN BUFFER ---");

    Serial.print("Min: ");
    int16_t minv = 32767;
    int16_t maxv = -32768;

    for (int i = 0; i < BUFFER_SAMPLES; i++) {
        if (voice_buffer[i] < minv) minv = voice_buffer[i];
        if (voice_buffer[i] > maxv) maxv = voice_buffer[i];
    }

    Serial.print("Min value: ");
    Serial.println(minv);
    Serial.print("Max value: ");
    Serial.println(maxv);

    Serial.println("FIN TEST");
}

void loop() {
    // nada
}
// -------- CONFIG TESTS --------
int sampleRates[] = {8000, 16000, 22050, 44100};
int numRates = 4;

#define SAMPLES_TEST 1024

// buffers pequeños para no reventar RAM
int16_t audio16[SAMPLES_TEST];
int32_t audio32[SAMPLES_TEST];

// ---------------- INIT I2S MIC ----------------
void setupMic(int sampleRate) {

    i2s_driver_uninstall(I2S_NUM_0);

    i2s_config_t mic_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = sampleRate,

        // 🔴 CLAVE: INMP441 requiere 32-bit
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,

        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 256,
        .use_apll = false
    };

    i2s_driver_install(I2S_NUM_0, &mic_config, 0, NULL);

    i2s_pin_config_t mic_pins = {
        .bck_io_num = MIC_SCK,
        .ws_io_num = MIC_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = MIC_SD
    };

    i2s_set_pin(I2S_NUM_0, &mic_pins);
}

// ---------------- INIT I2S SPK ----------------
void setupSpeaker(int sampleRate) {

    i2s_driver_uninstall(I2S_NUM_1);

    i2s_config_t spk_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = sampleRate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 256,
        .use_apll = false
    };

    i2s_driver_install(I2S_NUM_1, &spk_config, 0, NULL);

    i2s_pin_config_t spk_pins = {
        .bck_io_num = SPK_BCLK,
        .ws_io_num = SPK_WS,
        .data_out_num = SPK_DOUT,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_set_pin(I2S_NUM_1, &spk_pins);
}

// ---------------- CAPTURA ----------------
void capture(int sampleRate) {

    size_t bytesRead = 0;

    Serial.println("\n==============================");
    Serial.printf("TEST SAMPLE RATE: %d\n", sampleRate);
    Serial.println("==============================");

    memset(audio32, 0, sizeof(audio32));

    i2s_read(I2S_NUM_0, audio32, sizeof(audio32), &bytesRead, portMAX_DELAY);

    int samples = bytesRead / 4;

    Serial.printf("Samples capturados: %d\n", samples);

    // ---- DEBUG RAW ----
    Serial.print("RAW[0..10]: ");
    for (int i = 0; i < 10; i++) {
        Serial.print(audio32[i]);
        Serial.print(" ");
    }
    Serial.println();

    // ---- convertir a 16-bit ----
    long sum = 0;

    for (int i = 0; i < samples && i < SAMPLES_TEST; i++) {
        audio16[i] = audio32[i] >> 14; // normalización INMP441
        sum += abs(audio16[i]);
    }

    Serial.printf("Nivel señal (avg): %ld\n", sum / samples);

    if (sum == 0) {
        Serial.println("⚠️ PROBLEMA: SIGUE EN 0 -> MIC NO ESTÁ ENVIANDO AUDIO");
    }

    // ---- PLAYBACK ----
    size_t bytesWritten;

    Serial.println("Reproduciendo...");
    i2s_write(I2S_NUM_1, audio16, samples * 2, &bytesWritten, portMAX_DELAY);
}

// ---------------- SETUP ----------------
void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n=== INICIO TEST AUDIO I2S ===");

    for (int i = 0; i < numRates; i++) {

        int sr = sampleRates[i];

        setupMic(sr);
        setupSpeaker(sr);

        delay(500);

        capture(sr);

        delay(1000);
    }

    Serial.println("\n=== FIN TEST ===");
}

void loop() {
    // no loop continuo, solo tests
}

        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,

        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,

        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
        .use_apll = false
    };

    i2s_driver_install(I2S_NUM_1, &spk_config, 0, NULL);

    i2s_pin_config_t spk_pins = {
        .bck_io_num = SPK_BCLK,
        .ws_io_num = SPK_WS,
        .data_out_num = SPK_DOUT,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_set_pin(I2S_NUM_1, &spk_pins);
}

// ---------------- SETUP ----------------
void setup() {

    Serial.begin(115200);
    delay(1000);

    Serial.println("\n=== INICIO AUDIO 16-BIT ===");

    voice_buffer = (int16_t*)malloc(BUFFER_SAMPLES * sizeof(int16_t));

    if (!voice_buffer) {
        Serial.println("ERROR: sin RAM");
        while (1);
    }

    setupMic();
    setupSpeaker();

    Serial.println("Grabando...");

    // ---------------- GRABACIÓN ----------------
    i2s_read(
        I2S_NUM_0,
        voice_buffer,
        BUFFER_SAMPLES * sizeof(int16_t),
        &bytes_read,
        portMAX_DELAY
    );

    Serial.println("Grabación completa");

    int samples = bytes_read / 2;

    // ---------------- DEBUG ----------------
    Serial.println("\n--- DEBUG AUDIO ---");
    Serial.printf("Samples: %d\n", samples);

    Serial.print("RAW[0..10]: ");
    for (int i = 0; i < 10; i++) {
        Serial.print(voice_buffer[i]);
        Serial.print(" ");
    }
    Serial.println();

    // nivel de señal
    long sum = 0;
    int16_t minv = 32767;
    int16_t maxv = -32768;

    for (int i = 0; i < samples; i++) {
        sum += abs(voice_buffer[i]);

        if (voice_buffer[i] < minv) minv = voice_buffer[i];
        if (voice_buffer[i] > maxv) maxv = voice_buffer[i];
    }

    Serial.printf("AVG signal: %ld\n", sum / samples);
    Serial.printf("Min: %d Max: %d\n", minv, maxv);

    Serial.println("--- PLAYBACK LOOP ---");
}

// ---------------- LOOP (REPRODUCCIÓN) ----------------
void loop() {

    size_t bytes_written;

    i2s_write(
        I2S_NUM_1,
        voice_buffer,
        BUFFER_SAMPLES * sizeof(int16_t),
        &bytes_written,
        portMAX_DELAY
    );

    delay(300);
}