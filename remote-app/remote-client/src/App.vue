<script setup lang="ts"></script>

<template lang="pug">
v-container(fluid)
  v-app
    v-app-bar(title="House")
      v-row(align="center" justify="start")
        v-col(cols="auto")
          RouterLink(to="/")
            v-btn(variant="tonal" rounded="xl" size="x-large") Led
        v-col(cols="auto")
          RouterLink(to="/lcd16")
            v-btn(variant="tonal" rounded="xl" size="x-large") Lcd
    v-navigation-drawer
      v-list
        v-list-item(title="Navigation drawer")
    v-main
      v-container
        RouterView
</template>
