<script setup lang="ts">
defineProps({
  label: String,
  icon: {
    type: String,
    required: false
  }
})

const emit = defineEmits(['change:lcdText'])

const lcd16Model = defineModel('lcd16Model')

function show() {
  console.log('From child: ' + lcd16Model.value.text)
  emit('change:lcdText', 'lcd16Model')
}
</script>

<template lang="pug">
v-container(fluid)
  v-text-field(
    variant="outlined"
    clearable
    :label="label"
    v-model="lcd16Model.text"
  )
  v-btn(
    variant="outlined"
    color="secondary"
    @click="show"
  ) Show
</template>
