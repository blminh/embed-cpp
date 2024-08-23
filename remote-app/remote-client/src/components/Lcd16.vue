<script setup lang="ts">
defineProps({
  label: String,
  icon: {
    type: String,
    required: false
  }
})

const emit = defineEmits(['change:lcdEmit'])

const lcdTextModel = defineModel('lcdTextModel')

function show() {
  console.log('From child: ' + lcdTextModel.value)
  emit('change:lcdEmit', 'lcdTextModel')
}
</script>

<template lang="pug">
v-container(fluid)
  v-text-field(
    variant="outlined"
    clearable
    :label="label"
    v-model="lcdTextModel"
  )
  v-btn(
    variant="outlined"
    color="primary"
    @click="show"
  ) Show
</template>
