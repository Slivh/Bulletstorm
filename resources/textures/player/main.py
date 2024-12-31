from PIL import Image

# Load the image
input_image_path = "003.png"  # Replace with your image path
output_image_path = "3.png"  # Output image

# Open the image
img = Image.open(input_image_path)

# Check if the image has an alpha channel
if img.mode != 'RGBA':
    img = img.convert('RGBA')

# Get the image width and height
width, height = img.size

# Make all the pixels in the 1st row transparent
for x in range(width):
    img.putpixel((x, 0), (0, 0, 0, 0))  # Set RGBA to fully transparent

# Save the modified image
img.save(output_image_path)
print(f"Saved the modified image as {output_image_path}")
