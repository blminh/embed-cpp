<script setup lang="ts"></script>

<template lang="pug">
v-container
  Led(
    v-for="item in items"
    :label="item.name"
    v-model:ledStatusModel="item.status"
    @update:ledStatus="changeStatus(item)"
  )
</template>

<script setup lang="ts">
import { ref } from 'vue'
import Led from '@/components/Led.vue'
import axios from 'axios'

const items = ref([
  { id: 1, name: 'Led 1', pin: 23, status: false },
  { id: 2, name: 'Led 2', pin: 26, status: false }
])

async function changeStatus(item) {
  console.log(`From parent: ${item.name} - ${item.status}`)

  axios
    .post('/api/change', item)
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
