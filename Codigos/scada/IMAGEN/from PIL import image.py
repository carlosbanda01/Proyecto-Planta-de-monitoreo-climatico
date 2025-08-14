# ... (código previo)

class SCADAApp:
    def __init__(self, root):
        self.root = root
        self.root.title("WEATHER STATION PUQUCHI")

        # Variables para sensores
        self.temp_var = DoubleVar()
        self.hum_sue_var = DoubleVar()
        self.hum_amb_var = DoubleVar()
        self.lluv_var = DoubleVar()
        self.rad_var = DoubleVar()
        self.pres_var = DoubleVar()
        self.anem_var = DoubleVar()

        self.create_widgets()

    def create_widgets(self):
        # Frame principal que contiene todo el contenido
        main_frame = ttk.Frame(self.root, padding="20")
        main_frame.grid(row=0, column=0, padx=50, pady=20, rowspan=8, columnspan=4)  # Ajusta el padx y columnspan

        # Título grande centrado arriba
        title_label = Label(main_frame, text="WEATHER STATION PUQUCHI", font=('Arial', 16, 'bold'))
        title_label.grid(row=0, column=0, columnspan=4, pady=10)  # Ajusta el columnspan

        # Marco izquierdo para sensores (2 columnas)
        sensor_frame = ttk.Frame(main_frame)
        sensor_frame.grid(row=1, column=0, padx=10, pady=10, rowspan=8, columnspan=2)  # Ajusta el columnspan

        # Configurar estilo para barras de progreso
        style = ttk.Style()
        style.configure("TProgressbar", thickness=30)

        # Etiquetas y barras de progreso para sensores (en dos columnas)
        self.create_sensor_widget(sensor_frame, "Temperatura:", self.temp_var, "red", row=1, column=0)
        self.create_sensor_widget(sensor_frame, "Humedad del Suelo:", self.hum_sue_var, "red", row=3, column=0)
        self.create_sensor_widget(sensor_frame, "Humedad del Ambiente:", self.hum_amb_var, "green", row=5, column=0)
        self.create_sensor_widget(sensor_frame, "Cantidad de Lluvia:", self.lluv_var, "green", row=7, column=0)
        self.create_sensor_widget(sensor_frame, "Radiación:", self.rad_var, "green", row=1, column=1)
        self.create_sensor_widget(sensor_frame, "Presión:", self.pres_var, "green", row=3, column=1)
        self.create_sensor_widget(sensor_frame, "Velocidad del Viento:", self.anem_var, "green", row=5, column=1)

        # Marco central para la imagen de la central
        central_frame = ttk.Frame(main_frame, padding="20")
        central_frame.grid(row=1, column=2, padx=10, pady=10, rowspan=8)

        # Imagen de la estación meteorológica
        self.show_image(central_frame, "./central.jpg", "Central")

        # Marco derecho para imágenes de la maqueta y la bomba
        right_frame = ttk.Frame(main_frame, padding="20")
        right_frame.grid(row=1, column=3, padx=10, pady=10, rowspan=8)

        # Otras imágenes
        self.imagen1 = Image.open("central.jpg").resize((200, 200))  # Redimensionar la imagen1
        self.imagen1 = ImageTk.PhotoImage(self.imagen1)

        self.imagen2 = Image.open("maqueta.jpg").resize((200, 200))  # Redimensionar la imagen2
        self.imagen2 = ImageTk.PhotoImage(self.imagen2)

        # Crear un widget de etiqueta para mostrar la imagen y posicionarlo
        self.label_imagen = ttk.Label(central_frame, image=self.imagen1)
        self.label_imagen.grid(row=



