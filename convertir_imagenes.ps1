# Script para convertir JPEG a PNG con transparencia
Add-Type -AssemblyName System.Drawing

function ConvertirATransparente {
    param(
        [string]$inputPath,
        [string]$outputPath,
        [string]$colorTransparente = "White"
    )
    
    # Cargar imagen original
    $bitmap = New-Object System.Drawing.Bitmap($inputPath)
    
    # Crear bitmap con soporte alpha (transparencia)
    $bitmapConAlpha = New-Object System.Drawing.Bitmap($bitmap.Width, $bitmap.Height, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    
    # Obtener el color a hacer transparente
    $colorTransp = [System.Drawing.Color]::$colorTransparente
    
    # Copiar píxeles y hacer transparente el color especificado
    for ($y = 0; $y -lt $bitmap.Height; $y++) {
        for ($x = 0; $x -lt $bitmap.Width; $x++) {
            $pixel = $bitmap.GetPixel($x, $y)
            
            # Si el píxel es blanco (o similar), hacerlo transparente
            if ($pixel.R -gt 240 -and $pixel.G -gt 240 -and $pixel.B -gt 240) {
                $bitmapConAlpha.SetPixel($x, $y, [System.Drawing.Color]::Transparent)
            } else {
                $bitmapConAlpha.SetPixel($x, $y, $pixel)
            }
        }
    }
    
    # Guardar como PNG
    $bitmapConAlpha.Save($outputPath, [System.Drawing.Imaging.ImageFormat]::Png)
    
    # Liberar recursos
    $bitmap.Dispose()
    $bitmapConAlpha.Dispose()
    
    Write-Host "Convertido: $inputPath -> $outputPath"
}

# Convertir las imágenes
$basePath = "c:\Users\mrcan\OneDrive\Documentos\GitHub\3E252\EjemplosJuego\assets\images"

ConvertirATransparente -inputPath "$basePath\j1.jpeg" -outputPath "$basePath\j1.png" -colorTransparente "White"
ConvertirATransparente -inputPath "$basePath\enemigo1.jpeg" -outputPath "$basePath\enemigo1.png" -colorTransparente "White"

Write-Host "¡Conversión completada!"
