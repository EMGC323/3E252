# Script para crear spritesheet de vaquero disparando
Add-Type -AssemblyName System.Drawing

# Crear imagen: 4 frames de 64x64 = 256x64 total
$width = 256
$height = 64
$frameWidth = 64
$frameHeight = 64

$bitmap = New-Object System.Drawing.Bitmap($width, $height)
$graphics = [System.Drawing.Graphics]::FromImage($bitmap)

# Color de fondo transparente (blanco)
$graphics.Clear([System.Drawing.Color]::White)

# Crear brush y pen
$redBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Red)
$bluePen = New-Object System.Drawing.Pen([System.Drawing.Color]::Blue, 2)
$blackBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Black)
$yellowBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Yellow)
$skinBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(210, 180, 140))

# Función para dibujar vaquero
function DibujarVaquero {
    param(
        [System.Drawing.Graphics]$g,
        [int]$xOffset,
        [int]$armRotation
    )
    
    $centerX = $xOffset + 32
    $centerY = 32
    
    # Cabeza
    $g.FillEllipse($skinBrush, $centerX - 6, $centerY - 16, 12, 12)
    
    # Sombrero
    $hatRect = New-Object System.Drawing.Rectangle($centerX - 10, $centerY - 20, 20, 4)
    $g.FillRectangle($blackBrush, $hatRect)
    
    # Cuerpo
    $g.FillRectangle($redBrush, $centerX - 4, $centerY - 4, 8, 12)
    
    # Brazo izquierdo (dibujable)
    $g.DrawLine($bluePen, $centerX - 4, $centerY, $centerX - 8 + ($armRotation * 2), $centerY + 4 + ($armRotation * 2))
    
    # Brazo derecho (disparo)
    # Posición del arma varía según el frame
    $gunX = $centerX + 6 + ($armRotation * 3)
    $gunY = $centerY - 2 - ($armRotation * 1)
    $g.FillRectangle($yellowBrush, $gunX, $gunY, 8, 2)
    
    # Piernas
    $g.FillRectangle($blackBrush, $centerX - 2, $centerY + 8, 2, 6)
    $g.FillRectangle($blackBrush, $centerX + 2, $centerY + 8, 2, 6)
}

# Dibujar 4 frames con diferentes posiciones del arma
for ($frame = 0; $frame -lt 4; $frame++) {
    $xOffset = $frame * 64
    DibujarVaquero -g $graphics -xOffset $xOffset -armRotation $frame
}

# Guardar imagen
$outputPath = "c:\Users\mrcan\OneDrive\Documentos\GitHub\3E252\EjemplosJuego\assets\images\vaquero_disparo_spritesheet.png"
$bitmap.Save($outputPath, [System.Drawing.Imaging.ImageFormat]::Png)

# Liberar recursos
$graphics.Dispose()
$bitmap.Dispose()
$redBrush.Dispose()
$bluePen.Dispose()
$blackBrush.Dispose()
$yellowBrush.Dispose()
$skinBrush.Dispose()

Write-Host "Spritesheet creado: $outputPath"
Write-Host "Dimensiones: 256x64 (4 frames de 64x64)"
