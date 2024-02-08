import javax.swing.*;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.category.DefaultCategoryDataset;

public class Dashboard extends JFrame {

    public Dashboard() {
        DefaultCategoryDataset dataset = new DefaultCategoryDataset();
        dataset.addValue(1.0, "Serie1", "Categoria1");
        dataset.addValue(4.0, "Serie1", "Categoria2");
        dataset.addValue(3.0, "Serie1", "Categoria3");

        JFreeChart chart = ChartFactory.createBarChart("Titolo Grafico", "Asse X", "Asse Y", dataset);
        ChartPanel chartPanel = new ChartPanel(chart);
        add(chartPanel);
        
        setTitle("Grafico con Java");
        setSize(800, 600);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Dashboard example = new Dashboard();
            example.setVisible(true);
        });
    }
}