<script setup lang="ts"></script>

<template lang="pug">
v-container(fluid)
  v-switch(
    class="reversed-switch"
    inset
    color="success"
    v-model="ledStatusModel"
  )
    template(v-slot:label)
      div.switch-label {{ label }}
</template>

<script setup lang="ts">
import { watch } from 'vue'

const props = defineProps<{
  label: string
}>()

const ledStatusModel = defineModel('ledStatusModel')

const emit = defineEmits(['update:ledStatus'])

watch(ledStatusModel, (val) => {
  console.log('From child: ' + val)
  emit('update:ledStatus', val)
})
</script>

<style>
.reversed-switch .v-input__control {
  display: flex;
  flex-direction: row-reverse;
  align-items: center;
}

.reversed-switch .v-switch__track {
  margin-right: 8px;
}

.reversed-switch .switch-label {
  margin-left: 8px;
}
</style>
