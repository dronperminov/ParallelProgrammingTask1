function Grid(canvas, nx, ny, k1, k2, variant, result, padding = 5) {
    this.canvas = canvas
    this.ctx = canvas.getContext('2d')

    this.nx = nx
    this.ny = ny
    this.k1 = k1
    this.k2 = k2
    this.variant = variant
    this.result = result

    this.padding = padding

    let size = Math.min(window.innerWidth, window.innerHeight) - 25
    this.cellSize = Math.max(100, (size - 2 * this.padding) / (Math.max(nx, ny)))
    this.radius = this.cellSize / 8

    canvas.width = this.padding * 2 + this.cellSize * nx + 100
    canvas.height = this.padding * 2 + this.cellSize * ny
}

Grid.prototype.DrawLine = function(x1, y1, x2, y2) {
    this.ctx.beginPath()
    this.ctx.moveTo(x1, y1)
    this.ctx.lineTo(x2, y2)
    this.ctx.stroke()
}

Grid.prototype.DrawVertex = function(x, y, id) {
    this.ctx.strokeStyle = '#000'
    this.ctx.fillStyle = '#03a9f4'

    this.ctx.beginPath()
    this.ctx.arc(x, y, this.radius, 0, Math.PI * 2)
    this.ctx.fill()
    this.ctx.stroke()

    this.ctx.fillStyle = '#fff'
    this.ctx.textAlign = 'center'
    this.ctx.textBaseline = 'middle'
    this.ctx.font = this.radius + 'px serif'
    this.ctx.fillText(id, x, y)
}

Grid.prototype.DrawGrid = function() {
    this.ctx.fillStyle = '#fff'
    this.ctx.fillRect(0, 0, 2 * this.padding + this.cellSize * this.nx, 2 * this.padding + this.cellSize * this.ny)
    this.ctx.strokeStyle = '#000'
    this.ctx.fillStyle = '#03a9f4'

    for (let i = 0; i <= this.ny; i++)
        this.DrawLine(this.padding, this.padding + i * this.cellSize, this.padding + this.nx * this.cellSize, this.padding + i * this.cellSize)

    for (let i = 0; i <= this.nx; i++)
        this.DrawLine(this.padding + i * this.cellSize, this.padding, this.padding + i * this.cellSize, this.padding + this.ny * this.cellSize)
}

Grid.prototype.DrawVerices = function() {
    let index = 0
    let vertex = 0
    let rectangles = 0
    let triangles = 0

    while (index < this.nx * this.ny) {
        for (let k = 0; k < this.k1 && index < this.nx * this.ny; k++) {
            let x = this.padding + (index % this.nx) * this.cellSize;
            let y = this.padding + Math.floor(index / this.nx) * this.cellSize;

            this.DrawVertex(x + this.cellSize / 2, y + this.cellSize / 2, vertex++)
            rectangles++
            index++
        }

        for (let k = 0; k < this.k2 && index < this.nx * this.ny; k++) {
            let x = this.padding + (index % this.nx) * this.cellSize
            let y = this.padding + Math.floor(index / this.nx) * this.cellSize

            if (this.variant == 'B1') {
                this.DrawLine(x, y, x + this.cellSize, y + this.cellSize)
                this.DrawVertex(x + this.cellSize / 3, y + this.cellSize * 2 / 3, vertex++)
                this.DrawVertex(x + this.cellSize * 2 / 3, y + this.cellSize / 3, vertex++)
            }
            else {
                this.DrawLine(x + this.cellSize, y, x, y + this.cellSize)
                this.DrawVertex(x + this.cellSize / 3, y + this.cellSize / 3, vertex++)
                this.DrawVertex(x + this.cellSize * 2 / 3, y + this.cellSize * 2 / 3, vertex++)
            }

            triangles += 2
            index++
        }
    }

    this.result.innerHTML = "<b>Прямоугольников:</b> " + rectangles
    this.result.innerHTML += "<br><b>Треугольников:</b> " + triangles
    this.result.innerHTML += "<br><b>Всего вершин:</b> " + vertex
}

Grid.prototype.DrawInfo = function() {
    let fsize = 20
    this.ctx.fillStyle = '#000'
    this.ctx.font = fsize + 'px serif'
    this.ctx.textAlign = 'left'
    this.ctx.textBaseline = 'top'

    this.ctx.fillText("Nx: " + this.nx, this.padding + this.nx * this.cellSize + 10, this.padding)
    this.ctx.fillText("Ny: " + this.ny, this.padding + this.nx * this.cellSize + 10, this.padding + fsize * 1)
    this.ctx.fillText("K1: " + this.k1, this.padding + this.nx * this.cellSize + 10, this.padding + fsize * 2)
    this.ctx.fillText("K2: " + this.k2, this.padding + this.nx * this.cellSize + 10, this.padding + fsize * 3)
}

Grid.prototype.Draw = function() {
    this.DrawGrid()
    this.DrawVerices()
    this.DrawInfo()
}