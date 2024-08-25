<script setup lang="ts"></script>

<template lang="pug">
v-container(fluid)
  Lcd(
    label="Lcd 16"
    v-model:lcd16Model="lcd16Reactive"
    @change:lcdText="showLcd"
  )
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import Lcd from '@/components/Lcd16.vue'
import axios from 'axios'

const lcd16Reactive = reactive({ text: '' })

function showLcd() {
  console.log('From parent: ' + lcd16Reactive.text)

  if (lcd16Reactive.text === null) lcd16Reactive.text = ''
  axios
    .post('/api/showLcd16', { ...lcd16Reactive })
    .then((res) => {
      console.log(`Send success! ${res.data}`)
      console.log(res)
    })
    .catch((err) => {
      console.log(`Error: ${err}`)
      console.log(err)
    })
}
</script>
