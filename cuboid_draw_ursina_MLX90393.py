from ursina import *
from serial import Serial, SerialException
# Set up serial connection
try:
    serialPort = Serial(port="COM6", baudrate=9600, timeout=0.5)
except SerialException:
    print("Could not open serial port. Please check the port name and your permissions.")
    exit()
# Initialize the Ursina engine
app = Ursina()
window.color = color.rgb(0, 0, 255)  # Set background to blue
# Create a red cuboid
cuboid = Entity(
    model='cube',
    color=color.red,
    scale=(4, .5, 2)
)

def setup_lighting():
    # Create a directional light
    directional_light = DirectionalLight()
    directional_light.look_at(Vec3(1, -1, -1))  # Direction the light is pointing towards
    directional_light.cast_shadow = True  # Enable casting shadows
    # Further configurations if you want to customize the light
    directional_light.shadow_map_size = 2048  # Higher values give better shadow resolution
    directional_light.falloff = 10  # Controls the light's attenuation
    directional_light.color = color.white

nw_text = None
def add_text_to_scene(text_string, x_position, y_position):
    global nw_text
    # If nw_text is None, this is the first time setting the text
    if nw_text is None:
        nw_text = Text(
            text=text_string,  # The text you want to display
            position=(x_position, y_position)  # The screen position for the text
        )
    else:
        # Update the text of the existing Text entity
        nw_text.text = text_string
def update():
    global nw_text
    if serialPort.inWaiting() > 0:
        data_bytes = serialPort.readline()
        try:
            data_str = data_bytes.decode('utf-8', errors='replace').strip()
            print(data_str)
            data_parts = data_str.split()
            # Check if all parts are present
            if len(data_parts) >= 6 and data_parts[0] == "X:" and data_parts[2] == "Y:" and data_parts[4] == "Z:":
                x = float(data_parts[1])  # X value
                y = float(data_parts[3])  # Y value
                z = float(data_parts[5])  # Z value
                # Update cuboid's rotation
                cuboid.rotation_x = 0
                cuboid.rotation_y = x % 360
                cuboid.rotation_z = 0

#                cuboid.rotation_x = -x % 360
#                cuboid.rotation_y = y % 360
#                cuboid.rotation_z = z % 360
            else:
                print(f"Incomplete or incorrect data received: {data_str}")
        except ValueError as e:
            print(f"Error parsing data: {e}")
            pass# Set the update function to be called every frame



def start():
    #app = Ursina()

    # Set up the scene with lighting
    setup_lighting()
    # Create a red cuboid

    ground = Entity(
        model='plane',
        scale=(10, 10, 10),
        color=color.gray,
        position=(0, -0.1, 0),
        receive_shadow=True
    )
   
    # Example to add ambient light to the scene
    AmbientLight(color=color.rgba(100, 100, 100, 100))
    EditorCamera()
    app.run()
if __name__ == '__main__':
    start()