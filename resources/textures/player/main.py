from PIL import Image

def move_pixels_up_and_make_bottom_transparent(image_path, output_path):
    # Open the image
    img = Image.open(image_path)
    
    # Convert the image to RGBA (if it's not already)
    img = img.convert("RGBA")
    
    # Get the width and height of the image
    width, height = img.size
    
    # Create a new image to store the modified pixels
    new_img = Image.new("RGBA", (width, height))
    new_pixels = []
    
    # Get the pixel data of the original image
    pixels = list(img.getdata())
    
    # Loop through the pixels and move them up by 2
    for y in range(2, height):
        for x in range(width):
            pixel = pixels[y * width + x]
            new_pixels.append(pixel)
    
    # Add transparency for the last 2 rows
    for _ in range(2 * width):
        new_pixels.append((0, 0, 0, 0))  # Transparent pixel
    
    # Create the new image with the updated pixel data
    new_img.putdata(new_pixels)
    
    # Save the new image
    new_img.save(output_path)

# Usage
input_image = 'orange.png'  # Replace with your PNG file path
output_image = '2.png'  # Replace with your desired output path
move_pixels_up_and_make_bottom_transparent(input_image, output_image)
