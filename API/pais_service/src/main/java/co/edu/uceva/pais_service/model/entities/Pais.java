package co.edu.uceva.pais_service.model.entities;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity //Esto es parte de JPA que es Java Persistence API
@Table(name = "pais")
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor

public class Pais {
    @GeneratedValue(strategy = GenerationType.IDENTITY)//esta anotacion incrementa el id automaticamente
    @Id
    private Long id;
    private String pais;
}
