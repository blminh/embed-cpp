<script setup lang="ts"></script>

<template lang="pug">
v-container(fluid)
  Lcd(
    label="Lcd 16"
    v-model:lcdTextModel="textLcdRef"
    @change:lcdEmit="showLcd"
    )
</template>

<script setup lang="ts">
import { ref } from 'vue'
import Lcd from '@/components/Lcd16.vue'

const textLcdRef = ref('')

function showLcd() {
  console.log('From parent: ' + textLcdRef.value)
}
</script>
