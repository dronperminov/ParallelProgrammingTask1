const RECTANGLE_COLOR = '#2196f3'//'#009688'
const UP_TRIANGLE_COLOR = '#2196f3'//'#ffbcd4'
const DOWN_TRIANGLE_COLOR = '#2196f3'//'#2196f3'

const EDGE_COLOR = '#ff5722'
const EDGE_LINE_WIDTH = 5

const MIN_CELL_SIZE = 80
const MIN_RADIUS = 12

const VARIANT_B1 = 'B1'
const VARIANT_B2 = 'B2'

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

    let size = (window.innerWidth < 768 ? window.innerWidth : window.innerWidth / 2)
    this.cellSize = (size - 2 * this.padding) / nx

    if (window.innerWidth < 768 && this.cellSize < MIN_CELL_SIZE)
        this.cellSize = MIN_CELL_SIZE

    this.radius = Math.max(this.cellSize / 8, MIN_RADIUS)

    canvas.width = this.padding * 2 + this.cellSize * nx
    canvas.height = this.padding * 2 + this.cellSize * ny
}

Grid.prototype.DrawLine = function(x1, y1, x2, y2) {
    this.ctx.beginPath()
    this.ctx.moveTo(x1, y1)
    this.ctx.lineTo(x2, y2)
    this.ctx.stroke()
}

// проверка, что вершина треугольная
Grid.prototype.IsTriangleVertex = function(v) {
    return v % (this.k1 + 2 * this.k2) >= this.k1
}

// проверка, что треугольная вершина сверху
Grid.prototype.IsUpVertex = function(v) {
    let pos = v % (this.k1 + 2 * this.k2)

    if (this.variant == VARIANT_B1)
        return pos >= this.k1 && !((pos - this.k1) & 1)

    return pos >= this.k1 && (pos - this.k1) & 1
}

// проверка, что треугольная вершина сверху
Grid.prototype.IsDownVertex = function(v) {
    let pos = v % (this.k1 + 2 * this.k2)

    if (this.variant == VARIANT_B1)
        return pos >= this.k1 && (pos - this.k1) & 1

    return pos >= this.k1 && !((pos - this.k1) & 1)
}

// получение координаты вершины на сетке
Grid.prototype.Vertex2Index = function(id) {
    let div = Math.floor(id / (this.k1 + 2 * this.k2))
    let mod = id % (this.k1 + 2 * this.k2)
    let pos = div * (this.k1 + this.k2)

    if (mod < this.k1)
        pos += mod
    else
        pos += Math.floor((mod + this.k1) / 2)

    return pos
}

// получение вершины по индексу
Grid.prototype.Index2Vertex = function(index) {
    let div = Math.floor(index / (this.k1 + this.k2))
    let mod = index % (this.k1 + this.k2)

    let vertex = div * (this.k1 + 2 * this.k2)

    if (mod < this.k1)
        vertex += mod
    else
        vertex += mod * 2 - this.k1

    return vertex
}

// формирование вершин
Grid.prototype.MakeVerices = function() {
    let index = 0
    let vertex = 0
    let rectangles = 0
    let triangles = 0

    this.vertices = []

    while (index < this.nx * this.ny) {
        for (let k = 0; k < this.k1 && index < this.nx * this.ny; k++) {
            let x = this.padding + (index % this.nx) * this.cellSize;
            let y = this.padding + Math.floor(index / this.nx) * this.cellSize;

            this.vertices.push({ x: x + this.cellSize / 2, y: y + this.cellSize / 2, id: vertex++ })

            rectangles++
            index++
        }

        for (let k = 0; k < this.k2 && index < this.nx * this.ny; k++) {
            let x = this.padding + (index % this.nx) * this.cellSize
            let y = this.padding + Math.floor(index / this.nx) * this.cellSize

            if (this.variant == VARIANT_B1) {
                this.vertices.push({ x: x + this.cellSize / 3, y: y + this.cellSize / 3, id: vertex++ })
                this.vertices.push({ x: x + this.cellSize * 2 / 3, y: y + this.cellSize * 2 / 3, id: vertex++ })
            }
            else {
                this.vertices.push({ x: x + this.cellSize / 3, y: y + this.cellSize * 2 / 3, id: vertex++ })
                this.vertices.push({ x: x + this.cellSize * 2 / 3, y: y + this.cellSize / 3, id: vertex++ })
            }

            triangles += 2
            index++
        }
    }

    this.result.innerHTML = "<b>Вариант:</b> " + this.variant
    this.result.innerHTML += "<br><b>Размер сетки:</b> " + this.nx + "x" + this.ny
    this.result.innerHTML += "<br><b>Параметры разбиения</b> " + this.k1 + ", " + this.k2
    this.result.innerHTML += "<br><br><b>Прямоугольников:</b> " + rectangles
    this.result.innerHTML += "<br><b>Треугольников:</b> " + triangles
    this.result.innerHTML += "<br><b>Всего вершин:</b> " + vertex
}

// формирование рёбер для заданной вершины для варианта B1
Grid.prototype.MakeEdgesForVertexB1 = function(v, x, y) {
    if (y > 0 && !this.IsDownVertex(v)) {
        let vertex = this.Index2Vertex((y - 1) * this.nx + x);

        if (this.IsTriangleVertex(vertex))
            vertex++;

        this.edges[v].push(vertex)
    }

    // соседняя слева
    if (x > 0 || (x == 0 && this.IsDownVertex(v)))
        this.edges[v].push(v - 1)

    this.edges[v].push(v)

    // соседняя справа
    if (x < this.nx - 1 || (x == this.nx - 1 && this.IsUpVertex(v)))
        this.edges[v].push(v + 1)

    // соседняя снизу, если не верхнетреугольная ячейка
    if (y < this.ny - 1 && !this.IsUpVertex(v))
        this.edges[v].push(this.Index2Vertex((y + 1) * this.nx + x))
}

// формирование рёбер для заданной вершины для варианта B2
Grid.prototype.MakeEdgesForVertexB2 = function(v, x, y) {
    // соседняя сверху, если не нижнетреугольная ячейка
    if (y > 0 && !this.IsDownVertex(v))
        this.edges[v].push(this.Index2Vertex((y - 1) * this.nx + x))

    // соседняя слева
    if (x > 0 || (x == 0 && this.IsUpVertex(v)))
        this.edges[v].push(v - 1)

    this.edges[v].push(v)

    // соседняя справа
    if (x < this.nx - 1 || (x == this.nx - 1 && this.IsDownVertex(v)))
        this.edges[v].push(v + 1)

    // соседняя снизу, если не верхнетреугольная ячейка
    if (y < this.ny - 1 && !this.IsUpVertex(v)) {
        let vertex = this.Index2Vertex((y + 1) * this.nx + x);

        if (this.IsTriangleVertex(vertex))
            vertex++;

        this.edges[v].push(vertex)
    }
}

// формирование рбер
Grid.prototype.MakeEdges = function() {
    this.edges = []

    for (let v = 0; v < this.vertices.length; v++) {
        this.edges[v] = []

        let index = this.Vertex2Index(v)
        let x = index % this.nx
        let y = Math.floor(index / this.nx)

        if (this.variant == VARIANT_B1) {
            this.MakeEdgesForVertexB1(v, x, y)
        }
        else {
            this.MakeEdgesForVertexB2(v, x, y)
        }
    }
}

// формирование массива IA
Grid.prototype.MakeIA = function() {
    let ia = []
    ia[0] = 0

    for (let i = 0; i < this.vertices.length; i++)
        ia[i + 1] = ia[i] + this.edges[i].length

    return ia
}

// формирование массива JA
Grid.prototype.MakeJA = function() {
    let ja = []
    let index = 0

    for (let i = 0; i < this.vertices.length; i++)
        for (let j = 0; j < this.edges[i].length; j++)
            ja[index++] = this.edges[i][j]

    return ja
}

// формирование списка смежности
Grid.prototype.MakeList = function() {
    let list = "<br><b>Список смежности:</b><br>"

    for (let i = 0; i < this.edges.length; i++)
        list += "<b>" + i + "</b>&rarr;[" + this.edges[i].join(", ") + "]<br>"

    return list
}

// отрисовка вершины
Grid.prototype.DrawVertex = function(vertex) {
    this.ctx.strokeStyle = EDGE_COLOR
    this.ctx.lineWidth = EDGE_LINE_WIDTH

    if (this.IsTriangleVertex(vertex.id)) {
        this.ctx.fillStyle = this.IsUpVertex(vertex.id) ? UP_TRIANGLE_COLOR : DOWN_TRIANGLE_COLOR
    }
    else {
        this.ctx.fillStyle = RECTANGLE_COLOR
    }

    this.ctx.beginPath()
    this.ctx.arc(vertex.x, vertex.y, this.radius, 0, Math.PI * 2)
    this.ctx.fill()
    this.ctx.stroke()

    this.ctx.fillStyle = '#fff'
    this.ctx.textAlign = 'center'
    this.ctx.textBaseline = 'middle'
    this.ctx.font = this.radius + 'px serif'
    this.ctx.fillText(vertex.id, vertex.x, vertex.y)
}

// отрисовка сетки
Grid.prototype.DrawGrid = function() {
    this.ctx.fillStyle = '#fff'
    this.ctx.fillRect(0, 0, 2 * this.padding + this.cellSize * this.nx, 2 * this.padding + this.cellSize * this.ny)
    this.ctx.strokeStyle = '#000'
    this.ctx.fillStyle = '#03a9f4'

    for (let i = 0; i <= this.ny; i++)
        this.DrawLine(this.padding, this.padding + i * this.cellSize, this.padding + this.nx * this.cellSize, this.padding + i * this.cellSize)

    for (let i = 0; i <= this.nx; i++)
        this.DrawLine(this.padding + i * this.cellSize, this.padding, this.padding + i * this.cellSize, this.padding + this.ny * this.cellSize)

    for (let index = this.k1; index < this.nx * this.ny; index += this.k1 + this.k2) {
        for (let k = 0; k < this.k2 && index + k < this.nx * this.ny; k++) {
            let x = this.padding + ((index + k) % this.nx) * this.cellSize
            let y = this.padding + Math.floor((index + k) / this.nx) * this.cellSize

            if (this.variant == VARIANT_B1) {
                this.DrawLine(x + this.cellSize, y, x, y + this.cellSize)
            }
            else {
                this.DrawLine(x, y, x + this.cellSize, y + this.cellSize)
            }
        }
    }
}

// отрисовка рёбер
Grid.prototype.DrawEdges = function() {
    for (let i = 0; i < this.edges.length; i++) {
        for (let j = 0; j < this.edges[i].length; j++) {
            let x1 = this.vertices[i].x
            let y1 = this.vertices[i].y

            let x2 = this.vertices[this.edges[i][j]].x
            let y2 = this.vertices[this.edges[i][j]].y

            this.ctx.strokeStyle = EDGE_COLOR
            this.ctx.lineWidth = EDGE_LINE_WIDTH
            this.DrawLine(x1, y1, x2, y2)
        }
    }
}

// отрисовка вершин
Grid.prototype.DrawVertices = function() {
    for (let i = 0; i < this.vertices.length; i++)
        this.DrawVertex(this.vertices[i])
}

Grid.prototype.AddResults = function() {
    let ia = this.MakeIA()
    let ja = this.MakeJA()
    this.result.innerHTML += "<br><br><b>IA:</b> [" + ia.join(", ") + "]"
    this.result.innerHTML += "<br><b>JA:</b> [" + ja.join(", ") + "]"
    this.result.innerHTML += "<br>" + this.MakeList()
}

// отрисовка
Grid.prototype.Draw = function() {
    this.MakeVerices()
    this.MakeEdges()

    this.DrawGrid()
    this.DrawEdges()
    this.DrawVertices()
    this.AddResults()
}