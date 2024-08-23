<script setup lang="ts"></script>

<template lang="pug">
v-container
    Led(
        label="Led 1"
        v-model:ledStatusModel="ledStatusRef"
        @update:ledStatus="changeStatus"
    )
</template>

<script setup lang="ts">
import { ref } from 'vue'
import Led from '@/components/Led.vue'
import axios from 'axios'

const ledStatusRef = ref(false)

async function changeStatus() {
  console.log('From parent: ' + ledStatusRef.value)

  axios
    .get('/api/change', {
      params: {
        status: ledStatusRef.value ? 1 : 0
      }
    })
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
