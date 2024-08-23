import axios from 'axios'
import { createPinia } from 'pinia'
import { createApp } from 'vue'
import 'vuetify/styles'
import App from './App.vue'
import vuetify from './plugins/vuetify'
import router from './router'

const app = createApp(App)

app.config.globalProperties.axios = axios

app.use(createPinia())
app.use(router)
app.use(vuetify)

app.mount('#app')
